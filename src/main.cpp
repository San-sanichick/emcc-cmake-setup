#include <iostream>
#include <vector>
#include <array>
#include <span>
#include <ranges>

#include <Logger.h>
#include "dyn_array_wrapper.hpp"
#include "vec2/vec2.hpp"




template<typename T>
void print(const std::span<T> s)
{
    for (auto el : s)
    {
        std::cout << unsigned(el) << ' ';
    }
    std::cout << std::endl;
}

template<typename T>
void printBuf(const T* buffer, const int size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << unsigned(buffer[i]) << ' ';
    }
    std::cout << std::endl;
}


#define BUFSIZE 10




int main()
{
    uint8_t* buffer = new uint8_t[BUFSIZE];
    
    for (size_t i = 0; i < BUFSIZE; i++)
    {
        buffer[i] = i;
    }
    
    DynArrayWrapper<uint8_t> bufWrapper(buffer, BUFSIZE);
    std::cout << sizeof(bufWrapper) << std::endl;
    std::cout << sizeof(std::span<uint8_t>) << std::endl;
    
    printBuf(buffer, BUFSIZE);
    printBuf(bufWrapper.data(), bufWrapper.size());

    buffer[5] = 69;

    std::cout << std::endl;
    printBuf(buffer, BUFSIZE);
    
    delete[] buffer;
    printBuf(bufWrapper.data(), bufWrapper.size());
}