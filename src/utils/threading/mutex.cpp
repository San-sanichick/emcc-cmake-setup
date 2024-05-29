#include "utils/threading/mutex.hpp"


namespace utils
{
    namespace threading
    {
        Mutex::Mutex()
            : locked(false)
            , mutex(PTHREAD_MUTEX_INITIALIZER)
        {}

        Mutex::~Mutex()
        {
            if (this->locked) this->unlock();
            this->destroy();
        }

        bool Mutex::tryLock()
        {
            auto res = pthread_mutex_trylock(&this->mutex) == 0;
            if (res) this->locked = true;
            return res;
        }

        bool Mutex::lock()
        {
            this->locked = true;
            return pthread_mutex_lock(&this->mutex) == 0;
        }

        bool Mutex::unlock()
        {
            this->locked = false;
            return pthread_mutex_unlock(&this->mutex) == 0;
        }

        bool Mutex::destroy()
        {
            return pthread_mutex_destroy(&this->mutex) == 0;
        }

        pthread_mutex_t* Mutex::getMutex()
        {
            return &this->mutex;
        }
    }
}