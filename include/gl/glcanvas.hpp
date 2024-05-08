#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include "render/renderer.hpp"
#include "gl/shader.hpp"
#include "gl/program.hpp"
#include "utils.hpp"

namespace gl
{
    template<class R>
    requires Extends<R, renderer::ILowLevelRenderer>
    class GLCanvas
    {
    public:
        GLCanvas(uint32_t id, int32_t w, int32_t h)
        {
            this->vb = id;
            this->ctx = id;
            
            this->w = w;
            this->h = h;

            // gl::GLShader vertSh(
            //     "#version 300 es\n"
            //     "layout (location = 0) in vec3 position;\n"
            //     "void main()\n"
            //     "{\n"
            //     "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
            //     "}",
            //     gl::VERTEX
            // );

            // gl::GLShader fragSh(
            //     "#version 300 es\n"
            //     "precision mediump float;\n"
            //     "out vec4 color;\n"
            //     "void main()\n"
            //     "{\n"
            //     "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
            //     "}",
            //     gl::FRAGMENT
            // );

            // this->program = new gl::GLProgram("test", { vertSh, fragSh });
            // this->program = new gl::GLProgram("test");

            this->renderer = new R(this->w, this->h);
        }

        ~GLCanvas()
        {
            delete this->renderer;
            // delete this->program;
        }
        
        void render(GLfloat r, GLfloat g, GLfloat b)
        {
            glViewport(0, 0, this->w, this->h);
            glDisable(GL_DEPTH_TEST);
            
            // static const GLfloat vBuffer[] =
            // {
            //     -0.5f, -0.5f, 0.0f,
            //     0.5f, -0.5f, 0.0f,
            //     0.0f, 0.5f, 0.0f
            // };
            
            // uint32_t VBO;
            // glGenBuffers(1, &VBO);

            // glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // glBufferData(GL_ARRAY_BUFFER, sizeof(vBuffer), vBuffer, GL_STATIC_DRAW);
            
            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            // glEnableVertexAttribArray(0);
            
            // glBindBuffer(GL_ARRAY_BUFFER, 0);

            {
                glClearColor(r, g, b, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                // glUseProgram(this->program->get_id());
                // glDrawArrays(GL_TRIANGLES, 0, 3);
                
                this->renderer->render(this->w, this->h);
            }

            // glDeleteBuffers(1, &VBO);
        }

    private:
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
        
        int32_t w, h;
        uint32_t vb;
        
        // gl::GLProgram* program;
        R* renderer;
    };
}

#endif