#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "logger.h"
#include <Logger.h>
#include "debug.h"
#include "vec2/vec2.h"

namespace emsc = emscripten;


float lerp(float a, float b, float t)
{
    LOG("Hello");
    ERR("OH NO");
    DEBUG_BLOCK({
        std::cout << "hello from debug mode" << std::endl;
    });

    LogInfo("Info log from lib");
    LogAlert("Alert log");
    LogWarning("Warn log");

    math::Vec2 v1(1, 2);
    math::Vec2 v2(4, 2);

    auto res = v1 + v2;

    LOG(v1.toString());
    LOG(v2.toString());
    
    LOG(res.toString());
    res += v1;
    LOG(res.toString());

    std::array<math::Vec2, 4> v;

    for (auto el : v)
    {
        LOG(el.toString());
    }

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
        .property("X", &math::Vec2::x)
        .property("Y", &math::Vec2::y)
        .function("set", &math::Vec2::set)
        .function("toString", &math::Vec2::toString);
}