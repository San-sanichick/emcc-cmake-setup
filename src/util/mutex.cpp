#include "util/mutex.hpp"


namespace util
{
    namespace threading
    {
        Mutex::Mutex()
        {
            pthread_mutexattr_init(&this->attr);
            pthread_mutexattr_settype(&this->attr, static_cast<int>(MutexType::Default));
            pthread_mutex_init(&this->mutex, &this->attr);
        }

        Mutex::Mutex(MutexType type)
        {
            pthread_mutexattr_init(&this->attr);
            pthread_mutexattr_settype(&this->attr, static_cast<int>(type));
            pthread_mutex_init(&this->mutex, &this->attr);
        }


        Mutex::~Mutex()
        {
            this->destroy();
        }

        uint32_t Mutex::lock()
        {
            return pthread_mutex_lock(&this->mutex);
        }

        uint32_t Mutex::unlock()
        {
            return pthread_mutex_unlock(&this->mutex);
        }

        uint32_t Mutex::destroy()
        {
            pthread_mutexattr_destroy(&this->attr);
            return pthread_mutex_destroy(&this->mutex);
        }
    }
}