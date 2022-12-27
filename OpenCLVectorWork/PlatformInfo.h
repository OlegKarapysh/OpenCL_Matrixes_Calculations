#pragma once

#include <CL/cl.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

bool GetCLPlatformsList(cl_platform_id*& platforms_id, cl_uint& n_platforms);

void OutCLPlatformsInfo(cl_platform_id* platforms_id, const cl_uint& n_platforms);
