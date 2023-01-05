#include "ErrorLogger.h"
#include <iostream>

void ErrorLogger::LogCantCreateFile()
{
    std::cout << "Error whilst creating file!" << std::endl;
}

void ErrorLogger::LogCantOpenFile()
{
    std::cout << "Error whilst opening file!" << std::endl;
}