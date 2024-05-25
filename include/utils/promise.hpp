#pragma once

#include <result.hpp>

#include "mutex.hpp"
#include "thread.hpp"
#include "cond.hpp"



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
            { }


            void resolve(T res)
            {
                if (this->done) return;

                this->mutex.lock();

                this->result = res;
                this->done = true;
                this->success = true;

                this->cond.signal();
                this->mutex.unlock();
            }

            void reject()
            {
                if (this->done) return;

                this->mutex.lock();

                this->done = true;
                this->success = false;

                this->cond.signal();
                this->mutex.unlock();
            }

            cpp::result<T, PromiseError> await()
            {
                this->mutex.lock();

                while(!this->done)
                {
                    this->cond.wait(mutex);
                }

                this->mutex.unlock();

                if (this->success)
                {
                    return this->result;
                }
                else
                {
                    return cpp::fail(PromiseError::Reject);
                }
            }

            bool isDone()
            {
                this->mutex.lock();
                bool done = this->done;
                this->mutex.unlock();

                return done;
            }

            bool isSuccessful()
            {
                this->mutex.lock();
                bool success = this->success;
                this->mutex.unlock();
                
                return success;
            }

            void close()
            {
                this->mutex.destroy();
            }

        private:
            T result;
            utils::threading::Mutex mutex;
            utils::threading::Condition cond;

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