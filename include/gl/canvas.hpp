#pragma once

#include <emscripten/html5.h>
#include <GLES2/gl2.h>


namespace gl
{
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
    };
}