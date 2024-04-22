#pragma once

#include "logger.hpp"


#ifdef DEBUG_BUILD
    #define DEBUG_BLOCK(...) do { __VA_ARGS__; } while(0)

    #define ASSERT(x, message) do { if (!(x)) { ASSERT_LOG(#x, message); } } while(0)
#else
    #define DEBUG_BLOCK(...)

    #define ASSERT(x, message)
#endif