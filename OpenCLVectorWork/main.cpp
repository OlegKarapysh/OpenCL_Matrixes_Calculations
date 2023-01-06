// OpenCLVectorWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>

#include "Matrix.h"
#include "PlatformInfo.h"
#include "DeviceInfo.h"
#include "FileWork.h"
#include "OpenCLwork.h"
#include "DEFINES.h"

ErrorLogger errLogger;
FileWork fileWork(errLogger);

unsigned char GetPlatformChoice(cl_uint n_platforms)
{
	unsigned char choice = 1;
	do
	{
		_tprintf(__TEXT("Enter the number of platform to work (from 1 to %u): "), n_platforms);
		choice = _getch();
		putchar(choice);
		putchar('\n');
		choice -= 0x30;
	} while (choice == 0 || choice > n_platforms);
	return choice;
}

unsigned char GetDeviceNumChoice(cl_uint n_devices)
{
	unsigned char device_num = 1;
	if (n_devices > 1)
	{
		do
		{
			_tprintf(__TEXT("Enter the number of device to work (from 1 to %u): "), n_devices);
			device_num = _getch();
			putchar(device_num);
			putchar('\n');
			device_num -= 0x30;
		} while (device_num == 0 || device_num > n_devices);
	}
	return device_num;
}

void GetMatrixDimensionsFromUser(
	unsigned& width
	, unsigned& height
	, unsigned& size
)
{
	using namespace std;
	cout << "Enter the width of the matrixes: ";
	cin >> width;
	cout << "Enter the height of the matrixes: ";
	cin >> height;
	size = width * height;
}

void InitMatrixes(
	const unsigned width
	, const unsigned height
	, Matrix<INF>& matr1
	, Matrix<INF>& matr2
	, Matrix<INF>& matr3
	, Matrix<INF>& matr4
	, Matrix<INF>& matr5
	, Matrix<INF>& result
)
{
	matr1.Resize(width, height);
	matr2.Resize(width, height);
	matr3.Resize(width, height);
	matr4.Resize(width, height);
	matr5.Resize(width, height);
	result.Resize(width, height);
}

unsigned GetMatrFillFromUser()
{
	using namespace std;
	unsigned choice;
	cout << endl << "Select filling type (default is 1):" << endl
		<< "1. Random numbers" << endl
		<< "2. Fixed number 5.5" << endl;
	cin >> choice;
	return choice;
}

void CreateBuffersForMatrixes(OpenCLwork& openCLwork, unsigned size)
{
	for (unsigned char i = 0; i < MATRIXES_COUNT - 1; ++i)
	{
		openCLwork.CreateCLBuffer(i, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	}
	openCLwork.CreateCLBuffer(MATRIXES_COUNT - 1, CL_MEM_WRITE_ONLY, sizeof(INF_BUFFER) * size);
}

void SetKernelArgsForMatrixes(OpenCLwork& openCLwork)
{
	for (unsigned char i = 0; i < MATRIXES_COUNT; ++i)
	{
		openCLwork.SetCLKernelArgsForBuffer(i, sizeof(cl_mem));
	}
}

void FillMatrByChoice(
	unsigned choice
	, unsigned width
	, unsigned height
	, Matrix<INF>& matr1
	, Matrix<INF>& matr2
	, Matrix<INF>& matr3
	, Matrix<INF>& matr4
	, Matrix<INF>& matr5
)
{
	switch (choice)
	{
	case FILL_FIXED:
		matr1.FillFixed(width, height, (INF)FIXED_NUM);
		matr2.FillFixed(width, height, (INF)FIXED_NUM);
		matr3.FillFixed(width, height, (INF)FIXED_NUM);
		matr4.FillFixed(width, height, (INF)FIXED_NUM);
		matr5.FillFixed(width, height, (INF)FIXED_NUM);
		break;
	default:
		matr1.FillRandom(width, height, (INF)FIXED_NUM);
		matr2.FillRandom(width, height, (INF)FIXED_NUM);
		matr3.FillRandom(width, height, (INF)FIXED_NUM);
		matr4.FillRandom(width, height, (INF)FIXED_NUM);
		matr5.FillRandom(width, height, (INF)FIXED_NUM);
	}
}

unsigned char GetFileOutputChoice()
{
	unsigned char choice = 1;
	do
	{
		_tprintf(__TEXT("\nDo you want to out resulting data to file (y/n)?"));
		choice = _getch();
		putchar(choice);
	} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
	return choice;
}

void WriteResultToFileByChoice(Matrix<INF>& result)
{
	using namespace std;

	char writeToFileChoice = 'n';
	cout << "Do you want to write the result to a file? [y/n]: ";
	cin >> writeToFileChoice;

	if (writeToFileChoice == 'y' || writeToFileChoice == 'Y')
	{
		fileWork.WriteResultToFile(result);
		cout << "The result has been written to file.";
		return;
	}

	cout << "The result has not been written to file.";
}

int main()
{
	cl_uint n_platforms, n_devices;
	cl_platform_id* platforms_id = NULL;
	cl_device_id* devices_id = NULL;
	cl_device_type device_type = CL_DEVICE_TYPE_ALL;
	cl_int error_code = 0;
	unsigned char choice = 1;
	unsigned char device_num = 1;
	char* file_data = NULL;
	DWORD file_size;
	Matrix<INF> matr1, matr2, matr3, matr4, matr5, matrResult;
	unsigned width, height, size;
	ULONGLONG  timeCopy, timeCalc;

	GetCLPlatformsList(platforms_id, n_platforms);
	OutCLPlatformsInfo(platforms_id, n_platforms);

	choice = GetPlatformChoice(n_platforms);

	GetCLDevicesList(device_type, platforms_id[choice - 1], devices_id, n_devices);
	OutCLDevicesInfo(devices_id, n_devices);

	OpenCLwork openCLwork(errLogger, MATRIXES_COUNT);
	openCLwork.CreateCLContext(n_devices, devices_id);

	device_num = GetDeviceNumChoice(n_devices);

	openCLwork.CreateCLCommandQueue(device_num);

	fileWork.ReadFileToChar((TCHAR*)KERNEL_FILE_NAME, file_data, file_size);
	_tprintf(__TEXT("Kernel text:\n"));
	printf("%s\n\n", file_data);

	openCLwork.CreateCLProgram((const char**)(&file_data));
	openCLwork.BuildCLProgram();

	openCLwork.CreateCLKernel(KERNEL_NAME);

	GetMatrixDimensionsFromUser(width, height, size);
	InitMatrixes(width, height, matr1, matr2, matr3, matr4, matr5, matrResult);

	CreateBuffersForMatrixes(openCLwork, size);
	//openCLwork.CreateCLBuffer(0, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	//openCLwork.CreateCLBuffer(1, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	//openCLwork.CreateCLBuffer(2, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	//openCLwork.CreateCLBuffer(3, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	//openCLwork.CreateCLBuffer(4, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	//openCLwork.CreateCLBuffer(5, CL_MEM_WRITE_ONLY, sizeof(INF_BUFFER) * size);

	SetKernelArgsForMatrixes(openCLwork);
	//openCLwork.SetCLKernelArgsForBuffer(0, sizeof(cl_mem));
	//openCLwork.SetCLKernelArgsForBuffer(1, sizeof(cl_mem));
	//openCLwork.SetCLKernelArgsForBuffer(2, sizeof(cl_mem));
	//openCLwork.SetCLKernelArgsForBuffer(3, sizeof(cl_mem));
	//openCLwork.SetCLKernelArgsForBuffer(4, sizeof(cl_mem));
	//openCLwork.SetCLKernelArgsForBuffer(5, sizeof(cl_mem));
	openCLwork.SetCLKernelArgs(6, sizeof(cl_uint), (void*)(&size));

	FillMatrByChoice(GetMatrFillFromUser(), width, height, matr1, matr2, matr3, matr4, matr5);

	timeCopy = GetTickCount64();
	openCLwork.CopyCLDataToMemObj(0, CL_TRUE, sizeof(INF_BUFFER) * size, matr1.GetInternalArray());
	openCLwork.CopyCLDataToMemObj(1, CL_TRUE, sizeof(INF_BUFFER) * size, matr2.GetInternalArray());
	openCLwork.CopyCLDataToMemObj(2, CL_TRUE, sizeof(INF_BUFFER) * size, matr3.GetInternalArray());
	openCLwork.CopyCLDataToMemObj(3, CL_TRUE, sizeof(INF_BUFFER) * size, matr4.GetInternalArray());
	openCLwork.CopyCLDataToMemObj(4, CL_TRUE, sizeof(INF_BUFFER) * size, matr5.GetInternalArray());
		
	_tprintf(__TEXT("Starting calculations...\n"));
	timeCalc = GetTickCount64();
	openCLwork.RunCLKernel(1, (size_t*)(&size), NULL);
	timeCalc = GetTickCount64() - timeCalc;
	_tprintf(__TEXT("The end of calculations.\n"));
	openCLwork.ReadCLDataFromMemObj(5, CL_TRUE, sizeof(INF_BUFFER) * size, matrResult.GetInternalArray());
	timeCopy = GetTickCount64() - timeCopy;
	std::cout << "Calculation time is " << timeCalc << "ms and full (with copying) time is " << timeCopy << "ms.\n";
	WriteResultToFileByChoice(matrResult);

	free(file_data);
	free(platforms_id);
	
	return 0;
}

