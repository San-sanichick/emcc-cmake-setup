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


        bool ReadWriteLock::readLock()
        {
            this->locked = true;
            return pthread_rwlock_rdlock(&this->rwlock) == 0;
        }

        bool ReadWriteLock::tryReadLock()
        {
            auto res = pthread_rwlock_tryrdlock(&this->rwlock) == 0;
            if (res) this->locked = true;
            return res;
        }


        bool ReadWriteLock::writeLock()
        {
            this->locked = true;
            return pthread_rwlock_wrlock(&this->rwlock) == 0;
        }

        bool ReadWriteLock::tryWriteLock()
        {
            auto res = pthread_rwlock_trywrlock(&this->rwlock) == 0;
            if (res) this->locked = true;
            return res;
        }


        bool ReadWriteLock::unlock()
        {
            this->locked = false;
            return pthread_rwlock_unlock(&this->rwlock) == 0;
        }
    }
}
