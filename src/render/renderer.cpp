#include "render/renderer.hpp"
#include "logger.hpp"


renderer::SkiaLowLevelRenderer::ColorSettings::ColorSettings()
{
    colorType = kRGBA_8888_SkColorType;
    pixFormat = GR_GL_RGBA8;
}

renderer::SkiaLowLevelRenderer::ColorSettings::ColorSettings(sk_sp<SkColorSpace> colorSpace)
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



renderer::SkiaLowLevelRenderer::SkiaLowLevelRenderer(uint32_t w, uint32_t h)
    : width(w), height(h)
{
    auto interface = GrGLInterfaces::MakeWebGL();
    auto context = GrDirectContexts::MakeGL();
    
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

renderer::SkiaLowLevelRenderer::~SkiaLowLevelRenderer() {}


void renderer::SkiaLowLevelRenderer::updateWidth(uint32_t w)
{
    this->width = w;
}

void renderer::SkiaLowLevelRenderer::updateHeight(uint32_t h)
{
    this->height = h;
}

void renderer::SkiaLowLevelRenderer::resize()
{
    this->remakeSurface();
}



void renderer::SkiaLowLevelRenderer::remakeSurface()
{
    auto interface = GrGLInterfaces::MakeWebGL();
    auto context = GrDirectContexts::MakeGL();
    
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



void renderer::SkiaLowLevelRenderer::draw(SkCanvas* canvas)
{
    canvas->clear(SK_ColorBLACK);

    SkPaint p;
    p.setAntiAlias(true);
    p.setColor(SK_ColorCYAN);

    canvas->drawCircle({ this->width / 2.0f, this->height / 2.0f }, 20, p);
}


void renderer::SkiaLowLevelRenderer::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

    auto canvas = this->surface->getCanvas();
    this->draw(canvas);
    
    // flush the surface so we have all the pixels available for reading
    auto surfacePtr = this->surface.get();
    skgpu::ganesh::FlushAndSubmit(surfacePtr);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

renderer::RGBAPixel renderer::SkiaLowLevelRenderer::getPixel(uint32_t x, uint32_t y)
{
    union renderer::RGBAPixel pixel;
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel.data);
    return pixel;
}