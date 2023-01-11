#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "Matrix.h"
#include "DEFINES.h"
#include "ErrorLogger.h"

struct FileWork
{
	ErrorLogger Logger = NULL;

	FileWork(const ErrorLogger& logger);
	bool ReadFileToChar(TCHAR* file_name, char*& file_data, DWORD& file_size);
	bool WriteResultToFile(Matrix<INF>& result);
};