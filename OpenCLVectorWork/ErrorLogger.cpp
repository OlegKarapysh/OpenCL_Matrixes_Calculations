#include "ErrorLogger.h"
#include <iostream>

void ErrorLogger::LogCantCreateFile()
{
    std::cout << "Error while creating file!" << std::endl;
}

void ErrorLogger::LogCantOpenFile()
{
    std::cout << "Error while opening file!" << std::endl;
}

void ErrorLogger::LogCantCreateContext(int error)
{
    std::cout << "Error " << error << " while creating context!" << std::endl;
}

void ErrorLogger::LogCantCreateCommandQueue(int error)
{
    std::cout << "Error " << error << " while creating command queue!" << std::endl;
}

void ErrorLogger::LogCantCreateCLProgram(int error)
{
    std::cout << "Error " << error << " while creating OpenCL program!" << std::endl;
}

void ErrorLogger::LogCantBuildCLProgram(int error)
{
    std::cout << "Error " << error << " while building OpenCL program!" << std::endl;
}

void ErrorLogger::LogCantCreateKernel(int error)
{
    std::cout << "Error " << error << " while creating kernel!" << std::endl;
}

void ErrorLogger::LogInvalidBufferNumber()
{
    std::cout << "Invalid buffer number, buffer was not created!" << std::endl;
}

void ErrorLogger::LogCantCreateMemObj(int error)
{
    std::cout << "Error " << error << " while creating memory object!" << std::endl;
}

void ErrorLogger::LogCantSetKernelArgs(int error)
{
    std::cout << "Error " << error << " while setting kernel args!" << std::endl;
}

void ErrorLogger::LogCantCopyDataToMemObj(int error)
{
    std::cout << "Error " << error << " while copying data to memory object!" << std::endl;
}

void ErrorLogger::LogCantReadDataFromMemObj(int error)
{
    std::cout << "Error " << error << " while reading data from memory object!" << std::endl;
}

void ErrorLogger::LogCantRunKernel(int error)
{
    std::cout << "Error " << error << " while trying to run kernel!" << std::endl;
}
