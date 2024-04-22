#pragma once

#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <gpu/GrBackendSurface.h>
#include <GrTypes.h>
#include <gpu/GrDirectContext.h>
#include <SkColorSpace.h>
#include <ganesh/gl/GrGLBackendSurface.h>
#include <ganesh/gl/GrGLDirectContext.h>
#include <ganesh/gl/GrGLMakeWebGLInterface.h>
#include <gl/GrGLInterface.h>
#include <gl/GrGLTypes.h>
#include <src/gpu/RefCntedCallback.h>
#include <src/gpu/ganesh/GrProxyProvider.h>
#include <src/gpu/ganesh/gl/GrGLDefines.h>
#include <SkSurface.h>
#include <SkCanvas.h>

namespace gl
{
    struct ColorSettings
    {
        ColorSettings(sk_sp<SkColorSpace> colorSpace)
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

        SkColorType colorType;
        GrGLenum pixFormat;
    };
    

    class Canvas
    {
    public:
        Canvas(uint32_t id, int32_t w, int32_t h);
        ~Canvas();
        
        void render(GLfloat r, GLfloat g, GLfloat b);

    private:
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
        GLuint programId;
        GLuint vShader, fShader;
        
        int32_t w, h;
        GLuint vb;
        
        sk_sp<SkSurface> surface;
    };
}