#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "logger.h"
#include "debug.h"
#include "vec2/vec2.h"

using namespace emscripten;


float lerp(float a, float b, float t)
{
    LOG("Hello");
    ERR("OH NO");
    DEBUG_BLOCK({
        std::cout << "hello" << std::endl;
    })
    return (1 - t) * a + t * b;
}

void getCanvas(val canvas)
{
    val ctx = canvas.call<val, std::string>("getContext", "2d");
    ctx.set("fillStyle", "red");
    ctx.call<void>("fillRect", 10, 10, 150, 100);
}

EMSCRIPTEN_BINDINGS(math)
{
    function("lerp", &lerp);
    function("getCanvas", &getCanvas);
    class_<math::Vec2>("Vec2")
        .constructor()
        .constructor<float, float>()
        .constructor<math::Vec2>()
        .property("X", &math::Vec2::X)
        .property("Y", &math::Vec2::Y)
        .function("set", &math::Vec2::set)
        .function("toString", &math::Vec2::toString);
}