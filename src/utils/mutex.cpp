#include "utils/mutex.hpp"


namespace utils
{
    namespace threading
    {
        Mutex::Mutex()
            : locked(false)
        {
            pthread_mutex_init(&this->mutex, nullptr);
        }

        Mutex::~Mutex()
        {
            if (this->locked) this->unlock();
            this->destroy();
        }

        uint32_t Mutex::tryLock()
        {
            auto res = pthread_mutex_trylock(&this->mutex);
            if (res != 0) this->locked = true;
            return res;
        }

        uint32_t Mutex::lock()
        {
            this->locked = true;
            return pthread_mutex_lock(&this->mutex);
        }

        uint32_t Mutex::unlock()
        {
            this->locked = false;
            return pthread_mutex_unlock(&this->mutex);
        }

        uint32_t Mutex::destroy()
        {
            return pthread_mutex_destroy(&this->mutex);
        }
    }
}