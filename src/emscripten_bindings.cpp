#include <emscripten/bind.h>

// #include <emscripten/val.h>
#include <iostream>
#include "dyn_array_wrapper.hpp"
#include "gl/glcanvas.hpp"
#include "logger.hpp"
// #include "timer.hpp"


namespace emsc = emscripten;

void getBuffer(const intptr_t data, size_t size)
{
    // Timer timer;
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


EMSCRIPTEN_BINDINGS(module)
{
    emsc::function("getBuffer", &getBuffer);
    
    emsc::class_<SkiaCanvas>("Canvas")
        .constructor<uint32_t, int32_t, int32_t>()
        .function("render", &SkiaCanvas::render)
        .function("getPixel", &SkiaCanvas::getPixel);
}