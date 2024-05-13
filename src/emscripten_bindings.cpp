#include <emscripten/bind.h>

#include <iostream>

#include "dyn_array_wrapper.hpp"
#include "gl/glcanvas.hpp"
#include "util/thread.hpp"
#include "logger.hpp"



namespace emsc = emscripten;

void getBuffer(const intptr_t data, size_t size)
{
    const auto ptr = reinterpret_cast<uint8_t*>(data);

    utils::ReadonlyDynArrayWrapper buffer(ptr, size);
    
    for (auto el : buffer)
    {
        std::cout << unsigned(el) << ' ';
    }
    std::cout << std::endl;
}



class SkiaCanvas
{
private:
    gl::GLCanvas<renderer::SkiaLowLevelRenderer> canvas;
    
public:
    SkiaCanvas(uint32_t ctx, int32_t w, int32_t h)
        : canvas(gl::GLCanvas<renderer::SkiaLowLevelRenderer>(ctx, w, h))
    {}
    
    void render()
    {
        this->canvas.render();
    }
    
    void getPixel(uint32_t x, uint32_t y)
    {
        auto pixel = this->canvas.getPixel(x, y);
        CORE_LOG("({}, {}): R {}, G {}, B {}", x, y, pixel.r, pixel.g, pixel.b);
    }
};


void threaded(std::string canvas1, std::string canvas2)
{
    auto foo = [](void* arg) -> void*
    {
        EmscriptenWebGLContextAttributes attrs {
            .alpha = 1,
            .depth = 1,
            .stencil = 1,
            .antialias = 1,
            .premultipliedAlpha = 0,
            .preserveDrawingBuffer = 0,
            .powerPreference = 0,
            .failIfMajorPerformanceCaveat = 1,

            .majorVersion = 2,
            .minorVersion = 1,
            
            .enableExtensionsByDefault = 0,
            .explicitSwapControl = 0,
            .proxyContextToMainThread = 0, // disallow
            .renderViaOffscreenBackBuffer = 1,
        };

        auto canvas = static_cast<std::string*>(arg);

        uint32_t ctx = emscripten_webgl_create_context(canvas->c_str(), &attrs);
        CORE_LOG("{}", ctx);
        SkiaCanvas c(ctx, 800, 600);
        c.render();
        c.getPixel(400, 300);

        return 0;
    };

    util::Thread t1(foo, &canvas1);
    emscripten_pthread_attr_settransferredcanvases(&(t1.attr), canvas1.c_str()); //! this is important
    t1.run();


    util::Thread t2(foo, &canvas2);
    emscripten_pthread_attr_settransferredcanvases(&(t2.attr), canvas2.c_str()); //! this is important
    t2.run();

    
    // t.join();

    // std::thread t2([&canvas2]()
    // {
    //     EmscriptenWebGLContextAttributes attrs {
    //         .alpha = 1,
    //         .depth = 1,
    //         .stencil = 1,
    //         .antialias = 1,
    //         .premultipliedAlpha = 0,
    //         .preserveDrawingBuffer = 0,
    //         .powerPreference = 0,
    //         .failIfMajorPerformanceCaveat = 1,

    //         .majorVersion = 2,
    //         .minorVersion = 1,
            
    //         .enableExtensionsByDefault = 0,
    //         .explicitSwapControl = 0,
    //         .proxyContextToMainThread = 0, // disallow
    //         .renderViaOffscreenBackBuffer = 1,
    //     };

    //     uint32_t ctx2 = emscripten_webgl_create_context(canvas2.c_str(), &attrs);

    //     SkiaCanvas c(ctx2, 800, 600);
    //     c.render();
    //     c.getPixel(400, 300);
    // });
}



EMSCRIPTEN_BINDINGS(module)
{
    emsc::function("getBuffer", &getBuffer);
    emsc::function("threaded", &threaded);
    
    emsc::class_<SkiaCanvas>("Canvas")
        .constructor<uint32_t, int32_t, int32_t>()
        .function("render", &SkiaCanvas::render)
        .function("getPixel", &SkiaCanvas::getPixel);
}