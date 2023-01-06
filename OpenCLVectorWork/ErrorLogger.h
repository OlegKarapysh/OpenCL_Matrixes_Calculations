#pragma once

struct ErrorLogger
{
    void LogCantCreateFile();
    void LogCantOpenFile();
    void LogCantCreateContext(int error);
    void LogCantCreateCommandQueue(int error);
    void LogCantCreateCLProgram(int error);
    void LogCantBuildCLProgram(int error);
    void LogCantCreateKernel(int error);
    void LogInvalidBufferNumber();
    void LogCantCreateMemObj(int error);
    void LogCantSetKernelArgs(int error);
    void LogCantCopyDataToMemObj(int error);
    void LogCantReadDataFromMemObj(int error);
    void LogCantRunKernel(int error);
};