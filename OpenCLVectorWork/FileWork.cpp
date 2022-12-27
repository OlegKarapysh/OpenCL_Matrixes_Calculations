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

bool WriteResultToFile(const float* res, const unsigned size)
{
	FILE* F = _tfopen(OUT_FILE_NAME, __TEXT("w+"));
	if (F)
	{
		fprintf(F, "The list of pairs: vector index - result value:\n");
		for (unsigned i = 0; i < size; i++)
			fprintf(F, "%u - %f\n", i, res[i]);
		return true;
	}
	return false;
}