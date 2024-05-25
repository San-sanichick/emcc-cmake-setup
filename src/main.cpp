#include <iostream>

#include "utils/threading.hpp"


int main()
{
    //! Async example
    auto foo = [](utils::threading::Promise<uint32_t>* promise) -> void*
    {
        utils::threading::sleep(2000);
        
        // promise->resolve(69);
        promise->reject();
        
        return nullptr;
    };

    utils::threading::Async<uint32_t> a(foo);
    auto res = a.await();

    if (res.has_value())
    {
        std::cout << "res: " << res.value() << std::endl;
    }
    else
    {
        std::cout << "promise rejected" << std::endl;
    }    


    //! Thread example
    utils::threading::ReadWriteLock rwlock; // to prevent race condition

    auto handler1 = [&rwlock](uint32_t* a) -> void*
    {
        utils::threading::sleep(1000);

        rwlock.writeLock();
        *a += 69;

        std::cout << "in thread: " << *a << std::endl;
        rwlock.unlock();

        return nullptr;
    };

    uint32_t val = 43;

    utils::threading::Thread<uint32_t> t1(handler1, &val);
    utils::threading::Thread<uint32_t> t2(handler1, &val);

    t1.run();
    t2.run();

    t1.join();
    t2.join();
    std::cout << "val: " << val << std::endl;
}