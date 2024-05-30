#pragma once

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

#include <pthread.h>
#include <time.h>
#include <functional>
#include <cstdint>

#include "utils/caller.hpp"


namespace utils
{
    namespace threading
    {
        void exit()
        {
            pthread_exit(nullptr);
        }

        void sleep(uint32_t ms)
        {
#ifdef __EMSCRIPTEN__
        emscripten_sleep(ms);
#else
        timespec ts;
        ts.tv_sec = ms * 0.001;
        ts.tv_nsec = (ms % 1000) * 1000000;
        nanosleep(&ts, &ts);
#endif
        }

        /**
         * @brief A wrapper around pthread thread
         */
        template<typename T>
        class Thread
        {
        public:
            Thread(std::function<void*(T*)> body, T* args)
                : caller(body, args)
            {
                pthread_attr_init(&this->attr);
            }
            Thread(const Thread& o) = delete;
            Thread(Thread&& o) = delete;

            // static void exit();
            // static void sleep(uint32_t ms);
            

            /**
             * @brief Creates and queues the thread to run
             * 
             * @return true on success;
             * @return false on failure.
             */
            bool run()
            {
                bool res = pthread_create(&this->ptid, &this->attr, &caller.call_static, &caller) == 0;
                if (res) pthread_attr_destroy(&this->attr);
                return res;
            }

            /**
             * @brief Wait for this thread to execute
             * 
             * @return true on success;
             * @return false on failure.
             */
            bool join()
            {
                return pthread_join(this->ptid, 0) == 0;
            }


            /**
             * @brief Stop the execution of this thread
             * 
             * @return true on success;
             * @return false on failure.
             */
            bool cancel()
            {
                return pthread_cancel(this->ptid) == 0;
            }


            /**
             * @brief Detach this thread 
             * 
             * @return true on success;
             * @return false on failure.
             */
            bool detach()
            {
                return pthread_detach(this->ptid) == 0;
            }

            bool operator==(const Thread& o)
            {
                return this->ptid == o.ptid;
            }

            bool operator!=(const Thread& o)
            {
                return this->ptid != o.ptid;
            }

            Thread& operator=(const Thread& o) = delete;
            Thread& operator=(Thread&& o) = delete;

            const pthread_t& getID()
            {
                return this->ptid;
            }

            pthread_attr_t& getAttr()
            {
                return this->attr;
            }
            

        private:
            pthread_t ptid;
            pthread_attr_t attr;

            utils::Caller<T, void> caller;
        };
    }
}