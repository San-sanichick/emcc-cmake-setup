#pragma once

#include <pthread.h>
#include <cstdint>


namespace utils
{
    namespace threading
    {
        /**
         * @brief A wrapper around pthread mutex
         * 
         */
        class Mutex
        {
        public:
            Mutex();
            ~Mutex();


            uint32_t lock();
            uint32_t tryLock();
            uint32_t unlock();
            uint32_t destroy();

        private:
            bool locked;
            pthread_mutex_t mutex;
        };
    }
}
