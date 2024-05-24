#include <iostream>
#include "utils/threading.hpp"


int main()
{
    utils::threading::ReadWriteLock rwlock;

    auto handler1 = [&rwlock](void* data) -> void*
    {
        auto a = static_cast<uint32_t*>(data);
        
        rwlock.writeLock();

        utils::threading::Thread::sleep(1000);

        *a += 69;

        std::cout << "in thread 1: " << *a << std::endl;
        rwlock.unlock();

        return nullptr;
    };

    auto handler2 = [&rwlock](void* data) -> void*
    {
        auto a = static_cast<uint32_t*>(data);
        
        rwlock.writeLock();
        *a += 42;

        utils::threading::Thread::sleep(500);

        std::cout << "in thread 2: " << *a << std::endl;
        rwlock.unlock();

        return nullptr;
    };


    uint32_t a = 12;

    utils::threading::Thread t1(handler1, &a);
    utils::threading::Thread t2(handler2, &a);

    std::cout << "before threads: " << a << std::endl;

    t1.run();
    t2.run();

    t1.join();
    std::cout << "after thread 1: " << a << std::endl;
    utils::threading::Thread::sleep(2000);
    // utils::threading::Thread::exit();

    t2.join();
    std::cout << "after thread 2: " << a << std::endl;
}