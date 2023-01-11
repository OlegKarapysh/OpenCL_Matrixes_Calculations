// OpenCLVectorWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "ConsoleInterface.h"

int main()
{
	ConsoleOutput consoleOut;
	ErrorLogger errLogger((IOutputService*)&consoleOut);
	FileWork fileWork(errLogger);
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

	SetKernelArgsForMatrixes(openCLwork);

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
	
	WriteResultToFileByChoice(matrResult, fileWork);

	free(file_data);
	free(platforms_id);
	
	return 0;
}

