#include <emscripten/bind.h>
#include "logger.h"

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
}