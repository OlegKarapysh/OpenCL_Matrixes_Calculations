#define _CRT_SECURE_NO_WARNINGS

#include "FileWork.h"

#define OUT_FILE_NAME		__TEXT("Res.txt")

bool ReadFileToChar(TCHAR* file_name, char*& file_data, DWORD& file_size)
{
	HANDLE hFile = CreateFile(file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD file_size = GetFileSize(hFile, NULL), read_size;
		file_data = (char*)malloc(file_size + 1);
		ReadFile(hFile, file_data, file_size, &read_size, NULL);
		file_data[file_size] = 0;
		CloseHandle(hFile);
		return file_size == read_size;
	}
	return false;
}

void WriteResultToFile(Matrix<INF>& result)
{
	FILE* resFile = _tfopen(OUT_FILE_NAME, __TEXT("w+"));
	if (resFile)
	{
		fprintf(resFile, "The list of pairs: matrix element index - result value:\n");
		for (unsigned i = 0; i < result.GetHeight(); i++)
		{
			for (unsigned j = 0; j < result.GetWidth(); j++)
			{
				fprintf(resFile, "(%u, %u) - %f\n", i, j, result[i]);
			}
		}
	}
}