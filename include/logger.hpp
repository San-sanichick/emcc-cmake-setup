#pragma once
#include <iostream>
#include <Logger.h>
#include <format>

#define CORE_LOG(x, ...) LogInfo << std::format(x, __VA_ARGS__) << std::endl;

#ifdef DEBUG_BUILD
    #define CORE_DLOG(x, ...) LogDebug << '/' << __FILE__ << ':' << __LINE__ << "> " << std::format(x, __VA_ARGS__) << std::endl 
    #define CORE_DERR(x, ...) LogError << '/' << __FILE__ << ':' << __LINE__ << "> " << std::format(x, __VA_ARGS__) << std::endl

    #define CORE_ASSERT_LOG(cond, message) \
        LogError << "Assertion '" << cond << "' failed in /" << __FILE__ << ':' << __LINE__ << " > " << message << std::endl
#else
    #define CORE_DLOG(x, ...)
    #define CORE_DERR(x, ...)

    #define CORE_ASSERT_LOG(cond, message)
#endif
