#pragma once
#include <iostream>

#ifdef DEBUG_BUILD
    #define CORE_LOG(x) std::cout << '/' << __FILE__ << ':' << __LINE__ << "> " << x << std::endl
    #define CORE_ERR(x) std::cerr << '/' << __FILE__ << ':' << __LINE__ << "> " << x << std::endl

    #define CORE_ASSERT_LOG(cond, message) \
        std::cerr << "Assertion '" << cond << "' failed in /" << __FILE__ << ':' << __LINE__ << " > " << message << std::endl
#else
    #define CORE_LOG(x)
    #define CORE_ERR(x)

    #define CORE_ASSERT_LOG(cond, message)
#endif
