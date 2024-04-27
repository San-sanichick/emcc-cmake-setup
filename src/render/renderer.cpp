#include "render/renderer.hpp"


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
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0, 0, 0, 0);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    context->resetContext(kRenderTarget_GrGLBackendState | kMisc_GrGLBackendState);
    
    GrGLFramebufferInfo info;
    info.fFBOID = 0;

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


void renderer::SkiaLowLevelRenderer::render(uint32_t w, uint32_t h)
{
    SkPaint p;
    p.setAntiAlias(true);
    p.setColor(SK_ColorCYAN);

    auto canvas = this->surface->getCanvas();
    canvas->drawCircle({ w / 2.0f, h / 2.0f }, 20, p);
}
