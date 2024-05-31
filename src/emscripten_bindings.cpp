#include <emscripten/bind.h>
#include <emscripten/threading.h>

#include <iostream>
#include <sole.hpp>


#include "gl/glcanvas.hpp"
#include "utils/threading.hpp"
#include "logger.hpp"
#include "utils/timer.hpp"



namespace emsc = emscripten;

// utils::WeakReadonlyDynArrayWrapper getBuffer(const intptr_t data, size_t size)
// {
//     const auto ptr = reinterpret_cast<uint8_t*>(data);

//     return utils::WeakReadonlyDynArrayWrapper(ptr, size);
// }



class SkiaCanvas
{
public:
    SkiaCanvas(uint32_t ctx, int32_t w, int32_t h)
        : canvas(gl::GLCanvas<renderer::SkiaLowLevelRenderer>(ctx, w, h))
    {}
    
    void render(double time)
    {
        this->canvas.render(time);
    }
    
    void getPixel(uint32_t x, uint32_t y)
    {
        auto pixel = this->canvas.getPixel(x, y);
        CORE_LOG("({}, {}): R {}, G {}, B {}", x, y, pixel.r, pixel.g, pixel.b);
    }

private:
    gl::GLCanvas<renderer::SkiaLowLevelRenderer> canvas;
};


// EM_JS(intptr_t, createContext, (emsc::val GL, emsc::val canvas, emsc::val attrs), 
// {
//     return GL.createContext(canvas, attrs);
// });

//! can only create context from canvases that are in the DOM
void threaded(std::string canvas1, std::string canvas2, const intptr_t data, size_t size)
{
    sole::uuid id = sole::uuid4();
    std::cout << id.ab << std::endl;

    auto foo = [&data, size](void* arg) -> void*
    {
        utils::Timer t;

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
        const auto ptr = reinterpret_cast<uint8_t*>(data);

        uint32_t ctx = emscripten_webgl_create_context(canvas->c_str(), &attrs);

        auto c = new gl::GLCanvas<renderer::SkiaLowLevelRenderer>(ctx, 800, 600);
        c->getFontData(ptr, size);



        struct UserData
        {
            double* time;
            gl::GLCanvas<renderer::SkiaLowLevelRenderer>* canvas;
        };

        auto data = new UserData();

        double lastTime = 0;
        data->time = &lastTime;
        data->canvas = c;

        auto render = [](double time, void* data) -> EM_BOOL
        {
            auto d = static_cast<UserData*>(data);
            
            auto lastTime = *d->time;
            auto canvas = d->canvas;

            auto frameTime = time - lastTime;
            canvas->render(frameTime);

            *d->time = time;
            return EM_TRUE;
        };

        utils::threading::sleep(2000);
        

        emscripten_request_animation_frame_loop(render, data);

        return nullptr;
    };

    utils::threading::Thread<void> t1(foo, &canvas1);
    emscripten_pthread_attr_settransferredcanvases(&t1.getAttr(), canvas1.c_str()); //! this is important
    t1.run();


    utils::threading::Thread<void> t2(foo, &canvas2);
    emscripten_pthread_attr_settransferredcanvases(&t2.getAttr(), canvas2.c_str()); //! this is important
    t2.run();

    // t1.cancel();
    // t1.join();
    // t2.join();
}

void test()
{
    utils::threading::ReadWriteLock rwlock;

    auto foo = [&rwlock](void* arg) -> void*
    {
        auto num = static_cast<int*>(arg);

        rwlock.writeLock();

        *num *= 2;
        CORE_LOG("from thread: {}", *num);

        rwlock.unlock();
        return 0;
    };

    int num = 32;
    utils::threading::Thread<void> t(foo, &num);

    CORE_LOG("before thread: {}", num);
    t.run();
    t.join();
    CORE_LOG("after thread: {}", num);
}


EMSCRIPTEN_BINDINGS(module)
{
    emsc::function("threaded", &threaded);
    emsc::function("test", &test);
    
    emsc::class_<SkiaCanvas>("Canvas")
        .constructor<uint32_t, int32_t, int32_t>()
        .function("render", &SkiaCanvas::render)
        .function("getPixel", &SkiaCanvas::getPixel);
}