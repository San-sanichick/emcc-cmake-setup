#pragma once
#include <iostream>

#ifdef DEBUG_BUILD
    #define LOG(x) std::cout << '/' << __FILE__ << ':' << __LINE__ << "> " << x << std::endl
    #define ERR(x) std::cerr << '/' << __FILE__ << ':' << __LINE__ << "> " << x << std::endl

    #define ASSERT_LOG(cond, message) \
        std::cerr << "Assertion '" << cond << "' failed in /" << __FILE__ << ':' << __LINE__ << " > " << message << std::endl;
#else
    #define LOG(x)
    #define ERR(x)
#endif
