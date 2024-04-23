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

#include "gl/shader.hpp"


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

#endif