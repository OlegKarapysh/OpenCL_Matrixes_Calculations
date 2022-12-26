#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/cl.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>


cl_int CreateCLContext(const cl_uint& n_devices, cl_device_id *devices_id, cl_context& context);
cl_int CreateCLCommandQueue(const cl_device_id& device_id, const cl_context& context, cl_command_queue& command_queue);

bool GetCLPlatformsList(cl_platform_id*& platforms_id, cl_uint& n_platforms);

bool GetCLDevicesList(const cl_device_type& device_type, const cl_platform_id& platform_id, cl_device_id*& devices_id, cl_uint& n_devices);

void OutCLDevicesInfo(cl_device_id* devices_id, const cl_uint& n_devices);
void OutCLPlatformsInfo(cl_platform_id* platforms_id, const cl_uint& n_platforms);

bool ReadFileToChar(TCHAR* FileName, char*& file_data);
