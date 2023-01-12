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
	INF* a, *b, *c, *d, *e, *f, *res;
	unsigned size, iterationsCount;
	ULONGLONG  timeCopy, timeCalc;

	GetCLPlatformsList(platforms_id, n_platforms);
	OutCLPlatformsInfo(platforms_id, n_platforms);

	choice = GetPlatformChoice(n_platforms);

	GetCLDevicesList(device_type, platforms_id[choice - 1], devices_id, n_devices);
	OutCLDevicesInfo(devices_id, n_devices);

	OpenCLwork openCLwork(errLogger, VECTORS_COUNT);
	openCLwork.CreateCLContext(n_devices, devices_id);

	device_num = GetDeviceNumChoice(n_devices);

	openCLwork.CreateCLCommandQueue(device_num);

	fileWork.ReadFileToChar((TCHAR*)KERNEL_FILE_NAME, file_data, file_size);
	_tprintf(__TEXT("Kernel text:\n"));
	printf("%s\n\n", file_data);

	openCLwork.CreateCLProgram((const char**)(&file_data));
	openCLwork.BuildCLProgram();

	openCLwork.CreateCLKernel(KERNEL_NAME);

	iterationsCount = GetNaturalNumberFromUser("Enter the number of iterations: ");
	size = GetNaturalNumberFromUser("Enter the size of vectors: ");
	InitVectors(size, a, b, c, d, e, f, res);

	CreateBuffersForVectors(openCLwork, size);

	SetKernelArgsForVectors(openCLwork);
	openCLwork.SetCLKernelArgs(VECTORS_COUNT, sizeof(cl_uint), (void*)(&size));

	FillVectorsByChoice(GetVectorsFillFromUser(), size, a, b, c, d, e, f);

	timeCopy = GetTickCount64();
	CopyVectorsToMemObjects(openCLwork, size, a, b, c, d, e, f);
		
	_tprintf(__TEXT("Starting calculations...\n"));
	timeCalc = GetTickCount64();
	for (register unsigned i = 0; i < iterationsCount; ++i)
		openCLwork.RunCLKernel(1, (size_t*)(&size), NULL);
	timeCalc = GetTickCount64() - timeCalc;
	_tprintf(__TEXT("The end of calculations.\n"));

	openCLwork.ReadCLDataFromMemObj(VECTORS_COUNT - 1, CL_TRUE, sizeof(INF_BUFFER) * size, res);
	timeCopy = GetTickCount64() - timeCopy;
	std::cout << "Calculation time is " << timeCalc << "ms and full (with copying) time is " << timeCopy << "ms.\n";
	
	WriteResultToFileByChoice(res, fileWork, size);

	free(file_data);
	free(platforms_id);
	
	return 0;
}

