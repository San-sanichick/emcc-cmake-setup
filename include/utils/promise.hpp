#pragma once

#include <result.hpp>

#include "mutex.hpp"
#include "thread.hpp"



namespace utils
{
    namespace threading
    {
        enum class PromiseError
        {
            Reject                
        };


        template<typename T>
        class Promise
        {
        public:

        public:
            Promise()
                : cond(PTHREAD_COND_INITIALIZER)
            { }


            void resolve(T res)
            {
                if (this->done) return;

                this->mutex.lock();

                this->result = res;
                this->done = true;
                this->success = true;

                pthread_cond_signal(&this->cond);
                this->mutex.unlock();
            }

            void reject()
            {
                if (this->done) return;

                this->mutex.lock();

                this->done = true;
                this->success = false;

                pthread_cond_signal(&this->cond);
                this->mutex.unlock();
            }

            cpp::result<T, PromiseError> await()
            {
                this->mutex.lock();

                while(!this->done)
                {
                    pthread_cond_wait(&this->cond, this->mutex.getMutex());
                }

                this->mutex.unlock();

                return this->success 
                            ? this->result 
                            : cpp::fail(PromiseError::Reject);
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

            bool success = false;
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

            cpp::result<T, PromiseError> await()
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