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

unsigned GetNaturalNumberFromUser(std::string message)
{
	using namespace std;
	int number = 0;
	do
	{
		cout << message;
		cin >> number;
	} while (number < 1);

	return number;
}

void InitVectors(const unsigned size, INF*& a, INF*& b, INF*& c, INF*& d, INF*& e, INF*& f, INF*& res)
{
	a = (INF*)malloc(size * sizeof(INF));
	b = (INF*)malloc(size * sizeof(INF));
	c = (INF*)malloc(size * sizeof(INF));
	d = (INF*)malloc(size * sizeof(INF));
	e = (INF*)malloc(size * sizeof(INF));
	f = (INF*)malloc(size * sizeof(INF));
	res = (INF*)malloc(size * sizeof(INF));
}

unsigned GetVectorsFillFromUser()
{
	using namespace std;
	unsigned choice;
	cout << endl << "Select filling type (default is 1):" << endl
		<< "1. Random numbers" << endl
		<< "2. Fixed number 5.5" << endl;
	cin >> choice;
	return choice;
}

void CreateBuffersForVectors(OpenCLwork& openCLwork, unsigned size)
{
	for (unsigned char i = 0; i < VECTORS_COUNT - 1; ++i)
	{
		openCLwork.CreateCLBuffer(i, CL_MEM_READ_ONLY, sizeof(INF_BUFFER) * size);
	}
	openCLwork.CreateCLBuffer(VECTORS_COUNT - 1, CL_MEM_WRITE_ONLY, sizeof(INF_BUFFER) * size);
}

void SetKernelArgsForVectors(OpenCLwork& openCLwork)
{
	for (unsigned char i = 0; i < VECTORS_COUNT; ++i)
	{
		openCLwork.SetCLKernelArgsForBuffer(i, sizeof(cl_mem));
	}
}

void FillVectorsByChoice(unsigned choice, unsigned size, 
	INF*& a, INF*& b, INF*& c, INF*& d, INF*& e, INF*& f)
{
	switch (choice)
	{
	case FILL_FIXED:
		for (unsigned i = 0; i < size; ++i)
		{
			a[i] = b[i] = c[i] = d[i] = e[i] = f[i] = (INF)FIXED_NUM;
		}
		break;
	default:
		srand((unsigned)time(NULL));
		for (unsigned i = 0; i < size; ++i)
		{
			a[i] = b[i] = c[i] = d[i] = e[i] = f[i] = (INF)(rand() + 1);
		}
	}
}

void CopyVectorsToMemObjects(OpenCLwork& oCLw, unsigned size, 
	INF*& a, INF*& b, INF*& c, INF*& d, INF*& e, INF*& f)
{
	oCLw.CopyCLDataToMemObj(0, CL_TRUE, sizeof(INF_BUFFER) * size, a);
	oCLw.CopyCLDataToMemObj(1, CL_TRUE, sizeof(INF_BUFFER) * size, b);
	oCLw.CopyCLDataToMemObj(2, CL_TRUE, sizeof(INF_BUFFER) * size, c);
	oCLw.CopyCLDataToMemObj(3, CL_TRUE, sizeof(INF_BUFFER) * size, d);
	oCLw.CopyCLDataToMemObj(4, CL_TRUE, sizeof(INF_BUFFER) * size, e);
	oCLw.CopyCLDataToMemObj(5, CL_TRUE, sizeof(INF_BUFFER) * size, f);
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

void WriteResultToFileByChoice(INF*& result, FileWork fw, unsigned size)
{
	using namespace std;

	char writeToFileChoice = 'n';
	cout << "Do you want to write the result to a file? [y/n]: ";
	cin >> writeToFileChoice;

	if (writeToFileChoice == 'y' || writeToFileChoice == 'Y')
	{
		fw.WriteResultToFile(result, size);
		cout << "The result has been written to file.";
		return;
	}

	cout << "The result has not been written to file.";
}