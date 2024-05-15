#include "utils/mutex.hpp"


namespace utils
{
    namespace threading
    {
        Mutex::Mutex()
        {
            pthread_mutex_init(&this->mutex, nullptr);
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
            return pthread_mutex_destroy(&this->mutex);
        }
    }
}