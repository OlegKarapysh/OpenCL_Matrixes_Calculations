#pragma once

#include "IOutputService.h"
#include <iostream>

struct ConsoleOutput : implements IOutputService
{
    void Out(std::string message)
    {
        std::cout << message;
    }
};