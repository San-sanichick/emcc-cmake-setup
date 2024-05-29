#include "utils/threading/cond.hpp"


namespace utils
{
    namespace threading
    {
        ConditionVariable::ConditionVariable()
            : cond(PTHREAD_COND_INITIALIZER)
        { }

        ConditionVariable::~ConditionVariable()
        {
            pthread_cond_destroy(&this->cond);
        }


        bool ConditionVariable::wait(utils::threading::Mutex& mutex)
        {
            return pthread_cond_wait(&this->cond, mutex.getMutex()) == 0;
        }

        bool ConditionVariable::waitTime(utils::threading::Mutex& mutex, uint32_t ms)
        {
            timespec ts;
            ts.tv_sec = ms * 0.001;
            ts.tv_nsec = (ms % 1000) * 1000000;
            return pthread_cond_timedwait(&this->cond, mutex.getMutex(), &ts) == 0;
        }


        bool ConditionVariable::broadcast()
        {
            return pthread_cond_broadcast(&this->cond) == 0;
        }

        bool ConditionVariable::signal()
        {
            return pthread_cond_signal(&this->cond) == 0;
        }
    }
}