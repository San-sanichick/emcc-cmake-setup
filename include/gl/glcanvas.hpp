#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <memory>

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
        GLCanvas(uint32_t ctx, int32_t w, int32_t h)
            : ctx(ctx)
            , width(w)
            , height(h)
            , vb(ctx)
        {
            this->renderer = std::make_unique<R>(this->width, this->height);
        }

        
        void render()
        {
            glViewport(0, 0, this->width, this->height);
            glDisable(GL_DEPTH_TEST);

            {
                glClearColor(0, 0, 0, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                
                this->renderer->render();
            }
        }
        
        renderer::RGBAPixel getPixel(uint32_t x, uint32_t y)
        {
            return this->renderer->getPixel(x, y);
        }

    private:
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
        
        uint32_t width, height;
        uint32_t vb;
        
        std::unique_ptr<R> renderer;
    };
}

#endif