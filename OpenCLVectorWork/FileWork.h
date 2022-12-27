#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

bool ReadFileToChar(TCHAR* file_name, char*& file_data, DWORD& file_size);
bool WriteResultToFile(const float* res, const unsigned size);