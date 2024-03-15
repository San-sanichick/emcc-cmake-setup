#include <iostream>
#include <Logger.h>
#include <vector>
#include <result.hpp>
#include "logger.hpp"
#include "debug.hpp"
#include "vec2/vec2.hpp"


auto divide(int32_t a, int32_t b) -> cpp::result<int32_t, std::errc>
{
    if (b == 0)
        return cpp::fail(static_cast<std::errc>(0));

    return a / b;
}


int main()
{
    auto res1 = divide(6, 2);
    auto res2 = divide(6, 0);
    
    std::cout << std::to_string(res1.value_or(0)) << std::endl;

    if (res2.has_error())
    {
        std::cout << "oh no" << std::endl;
    }

    // LOG("Hello");
    // ERR("OH NO");
    // DEBUG_BLOCK({
    //     std::cout << "hello from debug mode" << std::endl;
    // });

    // LogInfo("Info log from lib");
    // LogAlert("Alert log");
    // LogWarning("Warn log");

    // std::vector<math::Vec2> v;
    // v.reserve(2);

    // math::Vec2 v1(6, 5);
    // math::Vec2 v2(10, 45);

    // v.push_back(std::move(v1));
    // v.push_back(std::move(v2));

    // for (auto vec : v)
    // {
    //     std::cout << vec.toString() << std::endl;
    // }

    // v.push_back(v1);
    // v.push_back(v2);
}