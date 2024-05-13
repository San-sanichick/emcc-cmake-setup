#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <memory>

#include "render/renderer.hpp"
#include "gl/shader.hpp"
#include "gl/program.hpp"
#include "utils.hpp"

namespace emsc = emscripten;



namespace gl
{
    /**
     * @brief Class that takes care of OpenGL initialization and manages the canvas
    */
    template<class R>
    requires Extends<R, renderer::ILowLevelRenderer>
    class GLCanvas
    {
    public:
        GLCanvas(uint32_t ctx, int32_t w, int32_t h)
            : ctx(ctx)
            , width(w)
            , height(h)
        {
            // set this context to be active, in case we switched it (we probably did)
            this->setCurrentContext();
            this->renderer = std::make_unique<R>(this->width, this->height);
        }

        ~GLCanvas()
        {
            this->setCurrentContext();
            emscripten_webgl_destroy_context(this->ctx);
        }

        
        void render()
        {
            // again, in case we switched contexts, we need to make this one current
            this->setCurrentContext();

            glViewport(0, 0, this->width, this->height);
            glDisable(GL_DEPTH_TEST);

            {
                glClearColor(0, 0, 0, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                
                this->renderer->render();
            }
            emscripten_webgl_commit_frame();
        }
        
        renderer::RGBAPixel getPixel(uint32_t x, uint32_t y)
        {
            this->setCurrentContext();
            return this->renderer->getPixel(x, y);
        }

    private:
        inline void setCurrentContext()
        {
            emscripten_webgl_make_context_current(this->ctx);
        }


    private:
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
        
        uint32_t width, height;
        
        std::unique_ptr<R> renderer;
    };
}

#endif