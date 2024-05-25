#pragma once

#include "mutex.hpp"
#include "thread.hpp"


namespace utils
{
    namespace threading
    {
        template<typename T>
        class Promise
        {
        public:
            Promise()
                : cond(PTHREAD_COND_INITIALIZER)
            { }


            void set(T res)
            {
                this->mutex.lock();

                this->result = res;
                this->done = true;

                pthread_cond_signal(&this->cond);
                this->mutex.unlock();
            }

            T await()
            {
                this->mutex.lock();

                while(!this->done)
                {
                    pthread_cond_wait(&this->cond, this->mutex.getMutex());
                }

                this->mutex.unlock();
                return this->result;
            }

            bool isDone()
            {
                this->mutex.lock();
                bool done = this->done;
                this->mutex.unlock();

                return done;
            }

            void close()
            {
                this->mutex.destroy();
                pthread_cond_destroy(&this->cond);
            }

        private:
            T result;
            utils::threading::Mutex mutex;
            pthread_cond_t cond;
            bool done = false;
        };

        template<typename T>
        class Future
        {
        public:
            Future(std::function<void*(Promise<T>*)> routine, Promise<T>* arg)
                : thread(routine, arg)
            {}

            void start()
            {
                this->thread.run();
            }

            void close()
            {
                this->thread.join();
            }

        private:
            utils::threading::Thread<Promise<T>> thread;
        };


        template<typename T>
        class Async
        {
        public:
            Async(std::function<void*(Promise<T>*)> routine)
                : future(routine, &this->promise)
            { }

            ~Async()
            {
                this->future.close();
                this->promise.close();
            }

            T await()
            {
                this->future.start();
                return this->promise.await();
            }
        
        private:
            utils::threading::Promise<T> promise;
            utils::threading::Future<T> future;
        };
    }
}