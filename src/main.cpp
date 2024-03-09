#include <iostream>
#include "logger.h"
#include <Logger.h>
#include <vector>
#include "debug.h"
#include "vec2/vec2.h"



int main()
{
    // LOG("Hello");
    // ERR("OH NO");
    // DEBUG_BLOCK({
    //     std::cout << "hello from debug mode" << std::endl;
    // });

    // LogInfo("Info log from lib");
    // LogAlert("Alert log");
    // LogWarning("Warn log");

    std::vector<math::Vec2> v;
    // v.reserve(2);

    math::Vec2 v1(6, 5);
    math::Vec2 v2(10, 45);

    v.push_back(std::move(v1));
    v.push_back(std::move(v2));

    // v.push_back(v1);
    // v.push_back(v2);
    
    // std::cout << "hello world" << std::endl;
}