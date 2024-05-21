#include "utils/thread.hpp"


namespace utils
{
    namespace threading
    {
        Thread::Thread(std::function<void*(void*)> body, void* args)
            : caller(body, args)
        {
            pthread_attr_init(&this->attr);
        }


        void Thread::exit()
        {
            pthread_exit(nullptr);
        }

        void Thread::sleep(uint32_t ms)
        {
            timespec ts;
            ts.tv_sec = ms * 0.001;
            ts.tv_nsec = (ms % 1000) * 1000000;
            nanosleep(&ts, &ts);
        }


        bool Thread::run()
        {
            bool res = pthread_create(&this->ptid, &this->attr, &caller.call_static, &caller) == 0;
            if (res) pthread_attr_destroy(&this->attr);
            return res;
        }

        bool Thread::join()
        {
            return pthread_join(this->ptid, 0) == 0;
        }

        bool Thread::cancel()
        {
            return pthread_cancel(this->ptid) == 0;
        }

        bool Thread::detach()
        {
            return pthread_detach(this->ptid) == 0;
        }



        bool Thread::operator==(const Thread& o)
        {
            return this->ptid == o.ptid;
        }

        bool Thread::operator!=(const Thread& o)
        {
            return this->ptid != o.ptid;
        }


        const pthread_t& Thread::getID()
        {
            return this->ptid;
        }

        pthread_attr_t& Thread::getAttr()
        {
            return this->attr;
        }
    }
}