#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/cl.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>


cl_int CreateCLContext(const cl_uint& n_devices, cl_device_id *devices_id, cl_context& context);

cl_int CreateCLCommandQueue(const cl_device_id& device_id, const cl_context& context, 
    cl_command_queue& command_queue);

cl_int CreateCLProgram(const cl_context& context, const char** prog_string, cl_program& program);

cl_int BuildCLProgram(cl_program& program);

cl_int CreateCLKernel(const cl_program& program, const char* kernel_name, cl_kernel& kernel);

cl_int CreateCLBuffer(const cl_context& context, cl_mem_flags flags, size_t size, cl_mem& mem_obj);

cl_int SetCLKernelArgs(const cl_kernel& context, cl_uint index, size_t size, const void* value);

cl_int CopyCLDataToMemObj(const cl_command_queue& command_queue, cl_mem& buf,
    cl_bool blocking, size_t size, const void* value);

cl_int ReadCLDataFromMemObj(const cl_command_queue& command_queue, cl_mem& buf,
    cl_bool blocking, size_t size, void* value);

cl_int RunCLKernel(const cl_command_queue& command_queue, const cl_kernel& kernel,
    cl_uint n_dim, size_t* global_work_size, size_t* local_work_size);
