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


            bool lock();
            bool tryLock();
            bool unlock();
            bool destroy();

        private:
            bool locked;
            pthread_mutex_t mutex;
        };
    }
}
