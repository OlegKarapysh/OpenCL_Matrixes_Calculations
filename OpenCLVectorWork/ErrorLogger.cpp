#include <iostream>
#include "ErrorLogger.h"

ErrorLogger::ErrorLogger(IOutputService* outputService)
{
    OutputService = outputService;
}

void ErrorLogger::LogCantCreateFile()
{
    OutputService->Out("Error while creating file!\n");
}

void ErrorLogger::LogCantOpenFile()
{
    OutputService->Out("Error while opening file!\n");
}

void ErrorLogger::LogCantCreateContext(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while creating context!\n");
}

void ErrorLogger::LogCantCreateCommandQueue(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while creating command queue!\n");
}

void ErrorLogger::LogCantCreateCLProgram(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while creating OpenCL program!\n");
}

void ErrorLogger::LogCantBuildCLProgram(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while building OpenCL program!\n");
}

void ErrorLogger::LogCantCreateKernel(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while creating kernel!\n");
}

void ErrorLogger::LogInvalidBufferNumber()
{
    OutputService->Out("Invalid buffer number, buffer was not created!\n");
}

void ErrorLogger::LogCantCreateMemObj(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while creating memory object!\n");
}

void ErrorLogger::LogCantSetKernelArgs(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while setting kernel args!\n");
}

void ErrorLogger::LogCantCopyDataToMemObj(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while copying data to memory object!\n");
}

void ErrorLogger::LogCantReadDataFromMemObj(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while reading data from memory object!\n");
}

void ErrorLogger::LogCantRunKernel(int error)
{
    OutputService->Out("Error " + std::to_string(error) + " while trying to run kernel!\n");
}
