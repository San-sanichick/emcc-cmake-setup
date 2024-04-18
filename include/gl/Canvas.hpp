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
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}";
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
    GLuint programId;
    GLuint vShader, fShader;
    
    int32_t w, h;
    GLuint vb;

public:
    Canvas(uint32_t id, int32_t w, int32_t h)
    {
        this->programId = glCreateProgram();
        
        this->vb = id;
        this->ctx = id;
        
        this->w = w;
        this->h = h;
        this->vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vertSh, NULL);
        glCompileShader(vShader);
        

        this->fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fracSh, NULL);
        glCompileShader(fShader);
        
        glAttachShader(this->programId, vShader);
        glAttachShader(this->programId, fShader);
        glLinkProgram(this->programId);
    }
    
    ~Canvas()
    {
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        glDeleteProgram(this->programId);
        
        delete[] vertSh;
        delete[] fracSh;
    }

    // https://groups.google.com/g/skia-discuss/c/P4GO92rxIaM
    void render(GLfloat r, GLfloat g, GLfloat b)
    {
        glViewport(0, 0, this->w, this->h);
        glDisable(GL_DEPTH_TEST);
        
        static const GLfloat vBuffer[] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        
        GLuint VBO;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vBuffer), vBuffer, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        {
            glClearColor(r, g, b, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(this->programId);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glDeleteBuffers(1, &VBO);
    }
};