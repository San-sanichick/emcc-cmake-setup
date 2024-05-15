#include "render/renderer.hpp"
#include "logger.hpp"
#include "debug.hpp"

#include "include/gpu/GrRecordingContext.h"
#include "include/private/gpu/ganesh/GrTypesPriv.h"
#include "src/gpu/ganesh/GrDirectContextPriv.h"
#include "src/gpu/ganesh/GrCaps.h"


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



    void SkiaLowLevelRenderer::draw(SkCanvas* canvas)
    {
        canvas->clear(SK_ColorBLACK);

        //! make texture
        GrGLint sampleCount;
        glGetIntegerv(GL_SAMPLES, &sampleCount);

        auto props = this->surface->props();
        auto ctx = canvas->recordingContext()->asDirectContext();
        auto tex = ctx->createBackendTexture(200, 100, SkColorType::kRGBA_8888_SkColorType, skgpu::Mipmapped::kNo, GrRenderable::kYes);
        //! end make texture

        //! get surface from the created texture
        auto surf = SkSurfaces::WrapBackendTexture(
            ctx,
            tex,
            GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,
            sampleCount,
            this->colorSettings.colorType,
            SkColorSpace::MakeSRGB(),
            &props
        );

        CORE_ASSERT(surf.get() != nullptr, "Surface creation silently failed");

        //! grab the canvas and render on it
        auto cv = surf->getCanvas();
        
        SkPaint p0;
        p0.setColor(SK_ColorGREEN);
        cv->drawCircle({ 100, 50 }, 50, p0);
        //! make the surface into an image
        auto img = surf->makeImageSnapshot();

        SkPaint p;
        p.setAntiAlias(true);
        p.setColor(SK_ColorCYAN);

        //! draw the image
        canvas->drawImage(img, 10, 10);
        canvas->drawCircle({ this->width / 2.0f, this->height / 2.0f }, 20, p);
    }


    void SkiaLowLevelRenderer::render()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

        auto canvas = this->surface->getCanvas();
        this->draw(canvas);
        
        // flush the surface so we have all the pixels available for reading
        auto surfacePtr = this->surface.get();
        skgpu::ganesh::FlushAndSubmit(surfacePtr);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    RGBAPixel renderer::SkiaLowLevelRenderer::getPixel(uint32_t x, uint32_t y)
    {
        union RGBAPixel pixel;
        glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel.data);
        return pixel;
    }
}