#pragma once

#include <emscripten/threading.h>
#include <pthread.h>
#include <functional>
#include "utils/caller.hpp"
#include "logger.hpp"


namespace utils
{
    namespace threading
    {
        /**
         * @brief A wrapper around pthread thread
         */
        class Thread
        {
        public:
            Thread(std::function<void*(void*)> body, void* args);
            Thread(const Thread& o) = delete;
            Thread(Thread&& o) = delete;

            static void exit();
            

            /**
             * @brief Creates and queues the thread to run
             */
            void run();

            uint32_t join();
            uint32_t cancel();
            uint32_t detach();

            bool operator==(const Thread& o);
            bool operator!=(const Thread& o);

            Thread& operator=(const Thread& o) = delete;
            Thread& operator=(Thread&& o) = delete;

            const pthread_t& getID();
            pthread_attr_t& getAttr();
            

        private:
            pthread_t ptid;
            pthread_attr_t attr;

            utils::Caller<void, void> caller;
        };
    }
}