#include "util/thread.hpp"


namespace util
{
    Thread::Thread(std::function<void*(void*)> body, void* args)
        : caller(body, args)
    {
        pthread_attr_init(&this->attr);
    }

    Thread::Thread(const Thread& o)
        : ptid(o.ptid)
        , attr(o.attr)
        , caller(o.caller)
    {};

    void Thread::exit()
    {
        pthread_exit(nullptr);
    }

    void Thread::run()
    {
        pthread_create(&this->ptid, &this->attr, &caller.call_static, &caller);
        pthread_attr_destroy(&this->attr);
    }

    uint32_t Thread::join()
    {
        return pthread_join(this->ptid, 0);
    }

    uint32_t Thread::cancel()
    {
        return pthread_cancel(this->ptid);
    }

    uint32_t Thread::detach()
    {
        return pthread_detach(this->ptid);
    }

    bool Thread::operator==(const Thread& o)
    {
        return pthread_equal(this->ptid, o.ptid) != 0;
    }

    bool Thread::operator!=(const Thread& o)
    {
        return !this->operator==(o); // lol
    }



    Thread::Caller::Caller(std::function<void*(void*)> body, void* arg)
        : body(body)
        , arg(arg)
    {}

    void* Thread::Caller::call_static(void* self)
    {
        return static_cast<Caller*>(self)->call();
    }

    void* Thread::Caller::call()
    {
        return this->body(this->arg);
    }
}