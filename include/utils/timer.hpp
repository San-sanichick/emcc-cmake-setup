#pragma once

#include <chrono>
#include <iostream>
#include "threading.hpp"


namespace utils
{
    class Timer
    {
    public:
        Timer()
            : start(std::chrono::steady_clock::now())
        {}

        ~Timer()
        {
            const auto end = std::chrono::steady_clock::now();
            const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            this->mutex.lock();
            std::cout << "Execution time: " << time.count() << "ms" << std::endl;
            this->mutex.unlock();
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> start;
        utils::threading::Mutex mutex;
    };
}