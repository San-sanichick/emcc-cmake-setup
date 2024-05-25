#include "utils/cond.hpp"


namespace utils
{
    namespace threading
    {
        Condition::Condition()
            : cond(PTHREAD_COND_INITIALIZER)
        { }

        Condition::~Condition()
        {
            pthread_cond_destroy(&this->cond);
        }


        bool Condition::wait(utils::threading::Mutex& mutex)
        {
            return pthread_cond_wait(&this->cond, mutex.getMutex()) == 0;
        }

        bool Condition::waitTime(utils::threading::Mutex& mutex, uint32_t ms)
        {
            timespec ts;
            ts.tv_sec = ms * 0.001;
            ts.tv_nsec = (ms % 1000) * 1000000;
            return pthread_cond_timedwait(&this->cond, mutex.getMutex(), &ts) == 0;
        }


        bool Condition::broadcast()
        {
            return pthread_cond_broadcast(&this->cond) == 0;
        }

        bool Condition::signal()
        {
            return pthread_cond_signal(&this->cond) == 0;
        }
    }
}