#pragma once

#include <chrono>
#include <iostream>



class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> start;
    
public:
    Timer()
        : start(std::chrono::steady_clock::now())
    {}

    ~Timer()
    {
        const auto end = std::chrono::steady_clock::now();
        const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Execution time: " << time << std::endl;
    }
};