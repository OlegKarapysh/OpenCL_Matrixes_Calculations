#include "ConsoleInterface.h"

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
	do
	{
		cout << "Enter the width of the matrixes: ";
		cin >> width;
	} while (width < 1);
	
	do
	{
		cout << "Enter the height of the matrixes: ";
		cin >> height;
	} while (height < 1);
	
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

void WriteResultToFileByChoice(Matrix<INF>& result, FileWork fw)
{
	using namespace std;

	char writeToFileChoice = 'n';
	cout << "Do you want to write the result to a file? [y/n]: ";
	cin >> writeToFileChoice;

	if (writeToFileChoice == 'y' || writeToFileChoice == 'Y')
	{
		fw.WriteResultToFile(result);
		cout << "The result has been written to file.";
		return;
	}

	cout << "The result has not been written to file.";
}