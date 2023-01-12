#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>

#include "PlatformInfo.h"
#include "DeviceInfo.h"
#include "FileWork.h"
#include "OpenCLwork.h"
#include "ConsoleOutput.h"
#include "DEFINES.h"

unsigned char GetPlatformChoice(cl_uint n_platforms);

unsigned char GetDeviceNumChoice(cl_uint n_devices);

unsigned GetNaturalNumberFromUser(std::string message);

void InitVectors(
	const unsigned size
	, INF*& a
	, INF*& b
	, INF*& c
	, INF*& d
	, INF*& e
	, INF*& f
	, INF*& res
);

unsigned GetVectorsFillFromUser();

void CreateBuffersForVectors(OpenCLwork& openCLwork, unsigned size);

void SetKernelArgsForVectors(OpenCLwork& openCLwork);

void FillVectorsByChoice(
	unsigned choice
	, unsigned size
	, INF*& a
	, INF*& b
	, INF*& c
	, INF*& d
	, INF*& e
	, INF*& f
);

void CopyVectorsToMemObjects(OpenCLwork& oCLw, unsigned size,
	INF*& a, INF*& b, INF*& c, INF*& d, INF*& e, INF*& f);

unsigned char GetFileOutputChoice();

void WriteResultToFileByChoice(INF*& result, FileWork fw, unsigned size);