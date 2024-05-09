#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include <include/gpu/ganesh/SkSurfaceGanesh.h>
#include <include/gpu/GrBackendSurface.h>
#include <include/gpu/GrTypes.h>
#include <include/gpu/GrDirectContext.h>
#include <include/core/SkColorSpace.h>
#include <include/gpu/ganesh/gl/GrGLBackendSurface.h>
#include <include/gpu/ganesh/gl/GrGLDirectContext.h>
#include <include/gpu/ganesh/gl/GrGLMakeWebGLInterface.h>
#include <include/gpu/gl/GrGLInterface.h>
#include <include/gpu/gl/GrGLTypes.h>
#include <src/gpu/RefCntedCallback.h>
#include <src/gpu/ganesh/GrProxyProvider.h>
#include <src/gpu/ganesh/gl/GrGLDefines.h>
#include <include/core/SkSurface.h>
#include <include/core/SkCanvas.h>


namespace renderer
{
    class ILowLevelRenderer
    {
    public:
        virtual void updateWidth(uint32_t w) = 0;
        virtual void updateHeight(uint32_t h) = 0;
        virtual void resize() = 0;
        virtual void render() = 0;
    };



    class SkiaLowLevelRenderer : public ILowLevelRenderer
    {
    public:
        SkiaLowLevelRenderer(uint32_t w, uint32_t h);
        virtual ~SkiaLowLevelRenderer();
        
        void updateWidth(uint32_t w) override;
        void updateHeight(uint32_t h) override;
        void resize() override;
        
        void render() override;
        void draw(SkCanvas* canvas);
        
    private:
        void remakeSurface();
        
    private:
        sk_sp<SkSurface> surface;
        uint32_t FBO;
        uint32_t width;
        uint32_t height;

        struct ColorSettings
        {
            ColorSettings();
            ColorSettings(sk_sp<SkColorSpace> colorSpace);

            SkColorType colorType;
            GrGLenum pixFormat;
        } colorSettings;
    };
}

#endif