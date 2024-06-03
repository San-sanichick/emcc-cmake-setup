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
#include <include/core/SkFont.h>
#include <include/core/SkFontMgr.h>
#include <include/core/SkData.h>




namespace renderer
{
    /**
     * @brief Represents a singular RGBA pixel with values 0-255
    */
    union RGBAPixel
    {
        uint8_t data[4];
        struct
        {
            uint8_t r, g, b, a;
        };
    };


    /**
     * @brief Base class for rendering
    */
    class ILowLevelRenderer
    {
    public:
        virtual void updateWidth(uint32_t w) = 0;
        virtual void updateHeight(uint32_t h) = 0;
        virtual void resize() = 0;
        virtual void render(double deltaTime) = 0;
        
        virtual void getFontData(uint8_t* ptr, size_t size) = 0;
        virtual RGBAPixel getPixel(uint32_t x, uint32_t y) = 0;
    };


    /**
     * @brief Derived class that does actual rendering
    */
    class SkiaLowLevelRenderer : public ILowLevelRenderer
    {
    public:
        SkiaLowLevelRenderer(uint32_t w, uint32_t h);
        virtual ~SkiaLowLevelRenderer();
        
        void updateWidth(uint32_t w) override;
        void updateHeight(uint32_t h) override;
        void resize() override;
        
        void render(double deltaTime) override;
        void draw(SkCanvas* canvas, double time);
        
        void getFontData(uint8_t* ptr, size_t size) override;
        RGBAPixel getPixel(uint32_t x, uint32_t y) override;

    private:
        void remakeSurface();
        static sk_sp<SkSurface> MakeTextureSurface(GrDirectContext *ctx, sk_sp<SkSurface>& surface, SkColorType colorType);
        
    private:
        sk_sp<SkSurface> surface;
        uint32_t FBO;
        uint32_t width;
        uint32_t height;

        SkFont font;

        float x = 0, y = 0;

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