#pragma once

#include <pthread.h>
#include <cstdint>

namespace utils
{
    namespace threading
    {
        /**
         * @brief A wrapper around pthread readers-writer lock
         * 
         */
        class ReadWriteLock
        {
        public:
            ReadWriteLock();
            ~ReadWriteLock();

            /**
             * @brief Wait until any other thread is done writing. Once lock is granted,
             * no other thread is allowed to write until the lock is released with ```unlock()```* 
             * @return true 
             * @return false 
             */
            bool readLock();
            bool tryReadLock();

            /**
             * @brief Wait until any other thread is done writing OR reading. Once lock is granted,
             * no other thread is allowed to write OR read until the lock is released with ```unlock()```
             * 
             * @return true 
             * @return false 
             */
            bool writeLock();
            bool tryWriteLock();

            bool unlock();

        private:
            bool locked;
            pthread_rwlock_t rwlock;
        };
    }
}
