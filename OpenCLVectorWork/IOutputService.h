#pragma once
#include <string>

#define implements

struct IOutputService
{
    virtual void Out(std::string message) = 0;
};