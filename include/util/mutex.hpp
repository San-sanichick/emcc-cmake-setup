#pragma once

#include <pthread.h>
#include <cstdint>


namespace util
{
    namespace threading
    {
        enum class MutexType : uint32_t
        {
            Default = PTHREAD_MUTEX_DEFAULT,
            Normal = PTHREAD_MUTEX_NORMAL,
            ErrorCheck = PTHREAD_MUTEX_ERRORCHECK,
            Recursive = PTHREAD_MUTEX_RECURSIVE
        };

        class Mutex
        {
        public:
            Mutex();
            Mutex(MutexType type);
            ~Mutex();


            uint32_t lock();
            uint32_t unlock();
            uint32_t destroy();

        private:
            pthread_mutex_t mutex;
            pthread_mutexattr_t attr;
        };
    }
}
