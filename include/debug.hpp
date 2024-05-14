#pragma once

#include <stdlib.h>
#include "logger.hpp"

#define DEBUG_BUILD


#ifdef DEBUG_BUILD
    #define CORE_DEBUG_BLOCK(...) do { __VA_ARGS__ } while(0)
    #define CORE_ABORT() abort()

    #define CORE_ASSERT(x, message) do { if (!(x)) { CORE_ASSERT_LOG(#x, message); CORE_ABORT(); } } while(0)
#else
    #define CORE_DEBUG_BLOCK(...)
    #define CORE_ABORT()

    #define CORE_ASSERT(x, message)
#endif