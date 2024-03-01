#include <emscripten/bind.h>
#include "logger.h"
#include "vec2/vec2.h"

using namespace emscripten;



float lerp(float a, float b, float t)
{
    LOG("Hello");
    ERR("OH NO");
    return (1 - t) * a + t * b;
}

EMSCRIPTEN_BINDINGS(math)
{
    function("lerp", &lerp);
    class_<math::Vec2>("Vec2")
        .constructor()
        .constructor<float, float>()
        .constructor<math::Vec2>()
        .property("X", &math::Vec2::X)
        .property("Y", &math::Vec2::Y)
        .function("set", &math::Vec2::set);
}