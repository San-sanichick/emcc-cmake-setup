#pragma once
#include <iostream>

#ifdef DEBUG
    #define LOG(x) std::cout << '/' << __FILE__ << ':' << __LINE__ << "> " << x << std::endl
    #define ERR(x) std::cerr << '/' << __FILE__ << ':' << __LINE__ << "> " << x << std::endl
#else
    #define LOG(x)
    #define ERR(x)
#endif

