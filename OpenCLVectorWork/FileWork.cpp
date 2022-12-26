#include "FileWork.h"

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