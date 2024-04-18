#pragma once

#include <emscripten/html5.h>
#include <GLES2/gl2.h>



class Canvas
{
private:
    const char* vertSh = 
        "#version 300 es\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}";

    const char* fracSh =
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}";
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
    GLuint programId;
    GLuint vShader, fShader;
    
    int32_t w, h;
    GLuint vb;

public:
    Canvas(uint32_t id, int32_t w, int32_t h);
    ~Canvas();
    
    void render(GLfloat r, GLfloat g, GLfloat b);
};