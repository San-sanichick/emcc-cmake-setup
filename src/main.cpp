#include <iostream>
#include "logger.h"
#include <Logger.h>
#include "debug.h"

int main()
{
    LOG("Hello");
    ERR("OH NO");
    DEBUG_BLOCK({
        std::cout << "hello from debug mode" << std::endl;
    });

    LogInfo("Info log from lib");
    LogAlert("Alert log");
    LogWarning("Warn log");

    std::cout << "hello world" << std::endl;
}