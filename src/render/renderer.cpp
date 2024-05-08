#include "render/renderer.hpp"
#include "logger.hpp"


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
{
    auto interface = GrGLInterfaces::MakeWebGL();
    auto context = GrDirectContexts::MakeGL();
    
    glGenRenderbuffers(1, &this->FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);


    context->resetContext(kRenderTarget_GrGLBackendState | kMisc_GrGLBackendState);
    
    GrGLFramebufferInfo info;
    info.fFBOID = this->FBO;

    auto colorSpace = SkColorSpace::MakeSRGB();
    const auto colorSettings = ColorSettings(colorSpace);
    info.fFormat = colorSettings.pixFormat;
    
    GrGLint sampleCount;
    GrGLint stencil;

    glGetIntegerv(GL_SAMPLES, &sampleCount);
    glGetIntegerv(GL_STENCIL_BITS, &stencil);

    auto target = GrBackendRenderTargets::MakeGL(w, h, sampleCount, stencil, info);

    this->surface = SkSurfaces::WrapBackendRenderTarget(
        context.get(),
        target,
        kBottomLeft_GrSurfaceOrigin,
        colorSettings.colorType,
        colorSpace,
        nullptr
    );
}

renderer::SkiaLowLevelRenderer::~SkiaLowLevelRenderer() {}


void renderer::SkiaLowLevelRenderer::render(uint32_t w, uint32_t h)
{
    glGenFramebuffers(1, &this->FBO);

    SkPaint p;
    p.setAntiAlias(true);
    p.setColor(SK_ColorCYAN);

    auto canvas = this->surface->getCanvas();
    canvas->drawCircle({ w / 2.0f, h / 2.0f }, 20, p);

    uint8_t pixel[4];
    glReadPixels(w / 2, h / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);

    CORE_LOG("R: {}, G: {}, B: {}", pixel[0], pixel[1], pixel[2]);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
