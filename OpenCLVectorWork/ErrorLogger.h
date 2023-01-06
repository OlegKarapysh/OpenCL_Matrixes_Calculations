#pragma once

struct ErrorLogger
{
    void LogCantCreateFile();
    void LogCantOpenFile();
    void LogCantCreateContext();
    void LogCantCreateCommandQueue();
    void LogCantCreateCLProgram();
    void LogCantBuildCLProgram();
    void LogCantCreateKernel();
    void LogInvalidBufferNumber();
    void LogCantCreateMemObj();
    void LogCantSetKernelArgs(int error);
    void LogCantCopyDataToMemObj(int error);
    void LogCantReadDataFromMemObj(int error);
    void LogCantRunKernel(int error);
};