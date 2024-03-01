#include <emscripten/bind.h>

#ifdef DEBUG
#include <iostream>
#endif

using namespace emscripten;

float lerp(float a, float b, float t)
{
#ifdef DEBUG
    std::cout << "hello" << std::endl;
#endif
    return (1 - t) * a + t * b;
}

EMSCRIPTEN_BINDINGS(math)
{
    function("lerp", &lerp);
}