#pragma once
#include <windows.h>
#include <tchar.h>

bool ReadFileToChar(TCHAR* file_name, char*& file_data, DWORD& file_size);