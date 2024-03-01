#pragma once
#include <iostream>

#ifdef DEBUG
    #define LOG(x) std::cout << x << std::endl;
    #define ERR(x) std::cerr << x << std::endl; 
#else
    #define LOG(x)
    #define ERR(x)
#endif

