#pragma once

#include <pthread.h>
#include <cstdint>


namespace utils
{
    namespace threading
    {
        class Mutex
        {
        public:
            Mutex();
            ~Mutex();


            uint32_t lock();
            uint32_t unlock();
            uint32_t destroy();

        private:
            pthread_mutex_t mutex;
        };
    }
}
