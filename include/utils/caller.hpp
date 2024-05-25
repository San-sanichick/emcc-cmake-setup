

namespace utils
{
    template<typename Arg, typename Ret>
    struct Caller
    {
        Caller(std::function<Ret*(Arg*)> body, Arg* arg)
            : body(body)
            , arg(arg)
        {}

        static Ret* call_static(void* self)
        {
            return static_cast<Caller*>(self)->call();
        }


        Ret* call()
        {
            return this->body(this->arg);
        }

    private:
        std::function<Ret*(Arg*)> body;
        Arg* arg;
    };
}