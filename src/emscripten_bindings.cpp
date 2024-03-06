#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "logger.h"
#include "debug.h"
#include "vec2/vec2.h"

namespace emsc = emscripten;


float lerp(float a, float b, float t)
{
    LOG("Hello");
    ERR("OH NO");
    DEBUG_BLOCK({
        std::cout << "hello from debug mode" << std::endl;
    })
    return (1 - t) * a + t * b;
}

void getCanvas(emsc::val canvas)
{
    emsc::val ctx = canvas.call<emsc::val, std::string>("getContext", "2d");
    ctx.set("fillStyle", "red");
    ctx.call<void>("fillRect", 10, 10, 150, 100);
}

EMSCRIPTEN_BINDINGS(math)
{
    emsc::function("lerp", &lerp);
    emsc::function("getCanvas", &getCanvas);
    emsc::class_<math::Vec2>("Vec2")
        .constructor()
        .constructor<float, float>()
        .constructor<math::Vec2>()
        .property("X", &math::Vec2::X)
        .property("Y", &math::Vec2::Y)
        .function("set", &math::Vec2::set)
        .function("toString", &math::Vec2::toString);
}