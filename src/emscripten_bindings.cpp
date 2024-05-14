#include <emscripten/bind.h>

#include <iostream>

#include "dyn_array_wrapper.hpp"
#include "gl/glcanvas.hpp"
#include "util/threading.hpp"
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


// EM_JS(intptr_t, createContext, (emsc::val GL, emsc::val canvas, emsc::val attrs), 
// {
//     return GL.createContext(canvas, attrs);
// });

//! can only create context from canvases that are in the DOM
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
            .powerPreference = EM_WEBGL_POWER_PREFERENCE_DEFAULT,
            .failIfMajorPerformanceCaveat = 1,

            .majorVersion = 2,
            .minorVersion = 1,
            
            .enableExtensionsByDefault = 0,
            .explicitSwapControl = 0,
            .proxyContextToMainThread = EMSCRIPTEN_WEBGL_CONTEXT_PROXY_DISALLOW,
            .renderViaOffscreenBackBuffer = 1,
        };

        auto canvas = static_cast<std::string*>(arg);

        uint32_t ctx = emscripten_webgl_create_context(canvas->c_str(), &attrs);

        SkiaCanvas c(ctx, 800, 600);
        c.render();
        c.getPixel(400, 300);

        return 0;
    };

    util::threading::Thread t1(foo, &canvas1);
    emscripten_pthread_attr_settransferredcanvases(&(t1.attr), canvas1.c_str()); //! this is important
    t1.run();


    util::threading::Thread t2(foo, &canvas2);
    emscripten_pthread_attr_settransferredcanvases(&(t2.attr), canvas2.c_str()); //! this is important
    t2.run();

    
    // t1.join();
    // t2.join();
}

void test()
{
    util::threading::Mutex mutex;

    auto foo = [&mutex](void* arg) -> void*
    {
        auto num = static_cast<int*>(arg);

        mutex.lock();

        *num = 69;
        CORE_LOG("from thread: {}", *num);

        mutex.unlock();
        return 0;
    };

    int num = 32;
    util::threading::Thread t(foo, &num);

    CORE_LOG("before thread: {}", num);
    t.run();
    t.join();
    CORE_LOG("after thread: {}", num);
}


EMSCRIPTEN_BINDINGS(module)
{
    emsc::function("getBuffer", &getBuffer);
    emsc::function("threaded", &threaded);
    emsc::function("test", &test);
    
    emsc::class_<SkiaCanvas>("Canvas")
        .constructor<uint32_t, int32_t, int32_t>()
        .function("render", &SkiaCanvas::render)
        .function("getPixel", &SkiaCanvas::getPixel);
}