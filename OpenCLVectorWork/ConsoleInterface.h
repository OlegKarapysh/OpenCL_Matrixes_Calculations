#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>

#include "Matrix.h"
#include "PlatformInfo.h"
#include "DeviceInfo.h"
#include "FileWork.h"
#include "OpenCLwork.h"
#include "DEFINES.h"

unsigned char GetPlatformChoice(cl_uint n_platforms);

unsigned char GetDeviceNumChoice(cl_uint n_devices);

void GetMatrixDimensionsFromUser(unsigned& width, unsigned& height, unsigned& size);

void InitMatrixes(
	const unsigned width
	, const unsigned height
	, Matrix<INF>& matr1
	, Matrix<INF>& matr2
	, Matrix<INF>& matr3
	, Matrix<INF>& matr4
	, Matrix<INF>& matr5
	, Matrix<INF>& result
);

unsigned GetMatrFillFromUser();

void CreateBuffersForMatrixes(OpenCLwork& openCLwork, unsigned size);

void SetKernelArgsForMatrixes(OpenCLwork& openCLwork);

void FillMatrByChoice(
	unsigned choice
	, unsigned width
	, unsigned height
	, Matrix<INF>& matr1
	, Matrix<INF>& matr2
	, Matrix<INF>& matr3
	, Matrix<INF>& matr4
	, Matrix<INF>& matr5
);

unsigned char GetFileOutputChoice();

void WriteResultToFileByChoice(Matrix<INF>& result, FileWork fw);