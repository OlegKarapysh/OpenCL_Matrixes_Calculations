#include "OpenCLwork.h"

OpenCLwork::OpenCLwork(const ErrorLogger& logger, const unsigned char buffersCount)
{
	_errLogger = logger;
	_buffers = new cl_mem[buffersCount];
	_nBuffers = buffersCount;
}

OpenCLwork::~OpenCLwork()
{
	ReleaseBuffers();
	if (_kernel != NULL)
		clReleaseKernel(_kernel);
	if (_program != NULL)
		clReleaseProgram(_program);
	if (_command_queue != NULL)
		clReleaseCommandQueue(_command_queue);
	if (_context != NULL)
		clReleaseContext(_context);
	if (_devicesId != NULL)
		free(_devicesId);
}

void OpenCLwork::ReleaseBuffers()
{
	for (unsigned char i = 0; i < _nBuffers; ++i)
	{
		clReleaseMemObject(_buffers[i]);
	}
	delete[] _buffers;
}

cl_int OpenCLwork::CreateCLContext(const cl_uint& n_devices, cl_device_id* devices_id)
{
	cl_int error;
	_context = clCreateContext(NULL, n_devices, devices_id, NULL, NULL, &error);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantCreateContext();
	}
	return error;
}

cl_int OpenCLwork::CreateCLCommandQueue(unsigned char deviceNum)
{
	cl_int error;
	_command_queue = clCreateCommandQueue(_context, _devicesId[deviceNum - 1], 0, &error);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantCreateCommandQueue();
	}
	return error;
}

cl_int OpenCLwork::CreateCLProgram(const char** prog_string)
{
	cl_int error;
	_program = clCreateProgramWithSource(_context, 1, prog_string, NULL, &error);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantCreateCLProgram();
	}
	return error;
}

cl_int OpenCLwork::BuildCLProgram()
{
	cl_int error = clBuildProgram(_program, 0, NULL, NULL, NULL, NULL);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantBuildCLProgram();
	}
	return error;
}

cl_int OpenCLwork::CreateCLKernel(const char* kernel_name)
{
	cl_int error;
	_kernel = clCreateKernel(_program, kernel_name, &error);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantCreateKernel();
	}
	return error;
}

cl_int OpenCLwork::CreateCLBuffer(unsigned char nBuffer, cl_mem_flags flags, size_t size)
{
	if (nBuffer >= _nBuffers)
	{
		_errLogger.LogInvalidBufferNumber();
		return CL_MEM_OBJECT_ALLOCATION_FAILURE;
	}

	cl_int error;
	_buffers[nBuffer] = clCreateBuffer(_context, flags, size, NULL, &error);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantCreateMemObj();
	}
	return error;
}

cl_int OpenCLwork::SetCLKernelArgs(cl_uint index, size_t size, const void* value)
{
	cl_int error = clSetKernelArg(_kernel, index, size, value);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantSetKernelArgs((int)error);
	}
	return error;
}

cl_int OpenCLwork::CopyCLDataToMemObj(unsigned char nBuffer, cl_bool blocking, size_t size, const void* value)
{
	if (nBuffer >= _nBuffers)
	{
		_errLogger.LogInvalidBufferNumber();
		return CL_INVALID_MEM_OBJECT;
	}

	cl_int error = clEnqueueWriteBuffer(
		_command_queue, _buffers[nBuffer], blocking, 0, size, value, 0, NULL, NULL);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantCopyDataToMemObj((int)error);
	}
	return error;
}

cl_int OpenCLwork::ReadCLDataFromMemObj(unsigned char nBuffer, cl_bool blocking, size_t size, void* value)
{
	if (nBuffer >= _nBuffers)
	{
		_errLogger.LogInvalidBufferNumber();
		return CL_INVALID_MEM_OBJECT;
	}

	cl_int error = clEnqueueReadBuffer(
		_command_queue, _buffers[nBuffer], blocking, 0, size, value, 0, NULL, NULL);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantReadDataFromMemObj((int)error);
	}
	return error;
}

cl_int OpenCLwork::RunCLKernel(cl_uint n_dim, size_t* global_work_size, size_t* local_work_size)
{
	cl_int error = clEnqueueNDRangeKernel(
		_command_queue, _kernel, n_dim, NULL, global_work_size, local_work_size, 0, NULL, NULL);
	if (error != CL_SUCCESS)
	{
		_errLogger.LogCantRunKernel((int)error);
	}
	return error;
}
