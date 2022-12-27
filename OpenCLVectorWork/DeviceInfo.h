#pragma once

#include <CL/cl.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

bool GetCLDevicesList(const cl_device_type& device_type, 
    const cl_platform_id& platform_id, cl_device_id*& devices_id, cl_uint& n_devices);

void OutCLDevicesInfo(cl_device_id* devices_id, const cl_uint& n_devices);