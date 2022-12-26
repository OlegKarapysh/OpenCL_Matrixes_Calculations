#include "OpenCLWork.h"

bool ReadFileToChar(TCHAR* file_name, char*& file_data, DWORD &file_size)
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

cl_int CreateCLProgram(const cl_context& context, const char** prog_string, cl_program& program)
{
	cl_int error;
	program = clCreateProgramWithSource(context, 1, prog_string, NULL, &error);
	return error;
}

cl_int BuildCLProgram(cl_program& program)
{
	return clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
}

cl_int CreateCLKernel(const cl_program& program, const char* kernel_name, cl_kernel &kernel)
{
	cl_int error;
	kernel = clCreateKernel(program, kernel_name, &error);
	return error;
}

cl_int CreateCLBuffer(const cl_context& context, cl_mem_flags flags, size_t size, cl_mem &mem_obj)
{
	cl_int error;
	mem_obj = clCreateBuffer(context, flags, size, NULL, &error);
	return error;
}

cl_int SetCLKernelArgs(const cl_kernel& kernel, cl_uint index, size_t size, const void* value)
{
	return clSetKernelArg(kernel, index, size, value);
}

cl_int CopyCLDataToMemObj(const cl_command_queue &command_queue, cl_mem &buf, cl_bool blocking, size_t size, const void* value)
{
	return clEnqueueWriteBuffer(command_queue, buf, blocking, 0, size, value, 0, NULL, NULL);
}

cl_int ReadCLDataFromMemObj(const cl_command_queue& command_queue, cl_mem& buf, cl_bool blocking, size_t size, void* value)
{
	return clEnqueueReadBuffer(command_queue, buf, blocking, 0, size, value, 0, NULL, NULL);
}

cl_int RunCLKernel(const cl_command_queue& command_queue, const cl_kernel& kernel, cl_uint n_dim, size_t* global_work_size, size_t* local_work_size)
{
	return clEnqueueNDRangeKernel(command_queue, kernel, n_dim, NULL, global_work_size, local_work_size, 0, NULL, NULL);
}