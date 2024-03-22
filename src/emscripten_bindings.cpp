#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <Logger.h>
#include <result.hpp>
#include "debug.hpp"
// #include "logger.hpp"
#include "vec2/vec2.hpp"

namespace emsc = emscripten;



auto divide(int32_t a, int32_t b) -> cpp::result<int32_t, std::errc>
{
    if (b == 0)
        return cpp::fail(static_cast<std::errc>(0));

    return a / b;
}

void test()
{
    auto res1 = divide(6, 2);
    auto res2 = divide(6, 0);
    
    std::cout << std::to_string(res1.value_or(0)) << std::endl;

    if (res2.has_error())
    {
        LogAlert("Divide by zero happened lmao");
    }
}

/* float lerp(float a, float b, float t)
{
    LOG("Hello");
    ERR("OH NO");
    DEBUG_BLOCK({
        std::cout << "hello from debug mode" << std::endl;
    });

    LogInfo("Info log from lib");
    LogAlert("Alert log");
    LogWarning("Warn log");

    return (1 - t) * a + t * b;
}

void getCanvas(emsc::val canvas)
{
    emsc::val ctx = canvas.call<emsc::val, std::string>("getContext", "2d");
    ctx.set("fillStyle", "red");
    ctx.call<void>("fillRect", 10, 10, 150, 100);
} */



EMSCRIPTEN_BINDINGS(math)
{
    emsc::function("test", &test);
    // emsc::function("lerp", &lerp);
    // emsc::function("getCanvas", &getCanvas);
    // emsc::class_<math::Vec2>("Vec2")
    //     .constructor()
    //     .constructor<float, float>()
    //     .constructor<math::Vec2>()
    //     .property("X", &math::Vec2::x)
    //     .property("Y", &math::Vec2::y)
    //     .function("set", &math::Vec2::set)
    //     .function("toString", &math::Vec2::toString);
}