#ifdef __EMSCRIPTEN__

// #include <include/ports/SkFontMgr_data.h>
#include <include/core/SkStream.h>
#include <src/ports/SkTypeface_FreeType.h>

#include "render/renderer.hpp"
#include "logger.hpp"
#include "debug.hpp"




namespace renderer
{
    SkiaLowLevelRenderer::ColorSettings::ColorSettings()
    {
        colorType = kRGBA_8888_SkColorType;
        pixFormat = GR_GL_RGBA8;
    }

    SkiaLowLevelRenderer::ColorSettings::ColorSettings(sk_sp<SkColorSpace> colorSpace)
    {
        if (colorSpace == nullptr || colorSpace->isSRGB())
        {
            colorType = kRGBA_8888_SkColorType;
            pixFormat = GR_GL_RGBA8;
        }
        else
        {
            colorType = kRGBA_F16_SkColorType;
            pixFormat = GR_GL_RGBA16F;
        }
    }

 
    SkiaLowLevelRenderer::SkiaLowLevelRenderer(uint32_t w, uint32_t h)
        : width(w), height(h)
    {
        auto interface = GrGLInterfaces::MakeWebGL();
        auto context = GrDirectContexts::MakeGL(interface);
        
        glGenRenderbuffers(1, &this->FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

        context->resetContext(kRenderTarget_GrGLBackendState | kMisc_GrGLBackendState);
        
        GrGLFramebufferInfo info;
        info.fFBOID = this->FBO;

        auto colorSpace = SkColorSpace::MakeSRGB();
        this->colorSettings = ColorSettings(colorSpace);
        info.fFormat = this->colorSettings.pixFormat;
        
        GrGLint sampleCount;
        GrGLint stencil;

        glGetIntegerv(GL_SAMPLES, &sampleCount);
        glGetIntegerv(GL_STENCIL_BITS, &stencil);

        auto target = GrBackendRenderTargets::MakeGL(this->width, this->height, sampleCount, stencil, info);

        this->surface = SkSurfaces::WrapBackendRenderTarget(
            context.get(),
            target,
            kBottomLeft_GrSurfaceOrigin,
            this->colorSettings.colorType,
            colorSpace,
            nullptr
        );
    }

    SkiaLowLevelRenderer::~SkiaLowLevelRenderer() {}


    void SkiaLowLevelRenderer::updateWidth(uint32_t w)
    {
        this->width = w;
    }

    void SkiaLowLevelRenderer::updateHeight(uint32_t h)
    {
        this->height = h;
    }

    void SkiaLowLevelRenderer::resize()
    {
        this->remakeSurface();
    }



    void SkiaLowLevelRenderer::remakeSurface()
    {
        auto interface = GrGLInterfaces::MakeWebGL();
        auto context = GrDirectContexts::MakeGL(interface);
        
        context->resetContext(kRenderTarget_GrGLBackendState | kMisc_GrGLBackendState);
        
        GrGLFramebufferInfo info;
        info.fFBOID = this->FBO;

        auto colorSpace = SkColorSpace::MakeSRGB();
        
        GrGLint sampleCount;
        GrGLint stencil;

        glGetIntegerv(GL_SAMPLES, &sampleCount);
        glGetIntegerv(GL_STENCIL_BITS, &stencil);

        auto target = GrBackendRenderTargets::MakeGL(
            this->width,
            this->height,
            sampleCount,
            stencil,
            info
        );

        this->surface = SkSurfaces::WrapBackendRenderTarget(
            context.get(),
            target,
            kBottomLeft_GrSurfaceOrigin,
            this->colorSettings.colorType,
            colorSpace,
            nullptr
        );
    }

    sk_sp<SkSurface> SkiaLowLevelRenderer::MakeTextureSurface(
        GrDirectContext *ctx, 
        sk_sp<SkSurface>& surface, 
        SkColorType colorType
    )
    {
        //! make texture
        GrGLint sampleCount;
        glGetIntegerv(GL_SAMPLES, &sampleCount);

        auto props = surface->props();
        auto tex = ctx->createBackendTexture(
            200, 100,
            SkColorType::kRGBA_8888_SkColorType, 
            skgpu::Mipmapped::kNo,
            GrRenderable::kYes
        );
        //! end make texture

        //! get surface from the created texture
        auto surf = SkSurfaces::WrapBackendTexture(
            ctx,
            tex,
            GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,
            sampleCount,
            colorType,
            SkColorSpace::MakeSRGB(),
            &props
        );

        CORE_ASSERT(surf.get() != nullptr, "Surface creation silently failed");
        return surf;
    }


    void SkiaLowLevelRenderer::render(double time)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

        auto canvas = this->surface->getCanvas();
        this->draw(canvas, time);
        
        // flush the surface so we have all the pixels available for reading
        auto surfacePtr = this->surface.get();
        skgpu::ganesh::FlushAndSubmit(surfacePtr);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }



    void SkiaLowLevelRenderer::draw(SkCanvas* canvas, double time)
    {
        canvas->clear(SK_ColorGRAY);

        // auto ctx = canvas->recordingContext()->asDirectContext();
        // auto surf = SkiaLowLevelRenderer::MakeTextureSurface(ctx, this->surface, this->colorSettings.colorType);

        //! grab the canvas and render on it
        // auto cv = surf->getCanvas();
        
        // SkPaint p0;
        // p0.setColor(SK_ColorGREEN);
        // cv->drawCircle({ 100, 50 }, 50, p0);
        // //! make the surface into an image
        // auto img = surf->makeImageSnapshot();

        SkPaint p;
        p.setAntiAlias(true);
        p.setColor(SK_ColorCYAN);

        //! draw the image
        // canvas->drawImage(img, 10, 10);
        this->x = (float)std::fmod(this->x + 10, this->width);
        this->y = this->height / 2.0f;

        canvas->drawCircle({ this->x, this->y }, 20, p);

        SkString str(std::to_string(time) + "ms");

        p.setColor(SK_ColorWHITE);
        canvas->drawString(str, this->width - 150.0f, 30, this->font, p);

        // canvas->drawCircle({ 450, 200 }, 69, p);
    }

    void SkiaLowLevelRenderer::getFontData(uint8_t* ptr, size_t size)
    {
        std::unique_ptr<SkMemoryStream> stream(new SkMemoryStream());
        stream->setMemoryOwned(ptr, size);
        auto tf = SkTypeface_FreeType::MakeFromStream(std::move(stream), SkFontArguments());

        this->font.setTypeface(tf);
        this->font.setSize(20);
    }

    RGBAPixel renderer::SkiaLowLevelRenderer::getPixel(uint32_t x, uint32_t y)
    {
        union RGBAPixel pixel;
        glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel.data);
        return pixel;
    }
}

#endif