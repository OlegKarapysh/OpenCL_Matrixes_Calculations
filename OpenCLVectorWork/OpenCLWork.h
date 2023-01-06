#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/cl.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "ErrorLogger.h"

class OpenCLwork
{
private:
    ErrorLogger _errLogger;
    unsigned char _nBuffers;
	cl_uint _nDevices = NULL;
	cl_device_id* _devicesId = NULL;
	cl_context _context = NULL;
	cl_command_queue _command_queue = NULL;
	cl_program _program = NULL;
	cl_kernel _kernel = NULL;
    cl_mem* _buffers;
	ULONGLONG  _timeCopy = 0, _timeCalc = 0;

public:
    OpenCLwork(const ErrorLogger& logger, unsigned char buffersCount);

    ~OpenCLwork();
    
    void ReleaseBuffers();

    cl_int CreateCLContext(const cl_uint& n_devices, cl_device_id* devices_id);

    cl_int CreateCLCommandQueue(unsigned char deviceNum);

    cl_int CreateCLProgram(const char** prog_string);

    cl_int BuildCLProgram();

    cl_int CreateCLKernel(const char* kernel_name);

    cl_int CreateCLBuffer(unsigned char nBuffer, cl_mem_flags flags, size_t size);

    cl_int SetCLKernelArgs(cl_uint index, size_t size, const void* value);

    cl_int CopyCLDataToMemObj(unsigned char nBuffer, cl_bool blocking, size_t size, const void* value);

    cl_int ReadCLDataFromMemObj(unsigned char nBuffer, cl_bool blocking, size_t size, void* value);

    cl_int RunCLKernel(cl_uint n_dim, size_t* global_work_size, size_t* local_work_size);
};
