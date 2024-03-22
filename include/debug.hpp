#pragma once

#ifdef DEBUG_BUILD
    #define DEBUG_BLOCK(...) do { __VA_ARGS__; } while(0)
#else
    #define DEBUG_BLOCK(...)
#endif