#pragma once

#include <pthread.h>
#include "mutex.hpp"

namespace utils
{
    namespace threading
    {
        class ConditionVariable
        {
        public:
            ConditionVariable();
            ~ConditionVariable();


            bool wait(utils::threading::Mutex& mutex);
            bool waitTime(utils::threading::Mutex& mutex, uint32_t ms);
            bool broadcast();
            bool signal();

        private:
            pthread_cond_t cond;
        };
    }
}