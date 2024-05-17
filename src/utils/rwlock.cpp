#include "utils/rwlock.hpp"

namespace utils
{
    namespace threading
    {
        ReadWriteLock::ReadWriteLock()
            : locked(false)
            , rwlock(PTHREAD_RWLOCK_INITIALIZER)
        { }

        ReadWriteLock::~ReadWriteLock()
        {
            if (this->locked) this->unlock();
            pthread_rwlock_destroy(&this->rwlock);
        }


        uint32_t ReadWriteLock::readLock()
        {
            this->locked = true;
            return pthread_rwlock_rdlock(&this->rwlock);
        }

        uint32_t ReadWriteLock::tryReadLock()
        {
            auto res = pthread_rwlock_tryrdlock(&this->rwlock);
            if (res != 0) this->locked = true;
            return res;
        }


        uint32_t ReadWriteLock::writeLock()
        {
            this->locked = true;
            return pthread_rwlock_wrlock(&this->rwlock);
        }

        uint32_t ReadWriteLock::tryWriteLock()
        {
            auto res = pthread_rwlock_trywrlock(&this->rwlock);
            if (res != 0) this->locked = true;
            return res;
        }


        uint32_t ReadWriteLock::unlock()
        {
            this->locked = false;
            return pthread_rwlock_unlock(&this->rwlock);
        }
    }
}
