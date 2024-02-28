#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
}