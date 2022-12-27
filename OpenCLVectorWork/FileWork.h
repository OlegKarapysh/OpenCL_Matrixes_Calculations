#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "Matrix.h"
#include "DEFINES.h"

bool ReadFileToChar(TCHAR* file_name, char*& file_data, DWORD& file_size);
void WriteResultToFile(Matrix<INF>& result);