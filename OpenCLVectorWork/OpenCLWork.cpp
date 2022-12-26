#include "OpenCLwork.h"

cl_int CreateCLContext(const cl_uint& n_devices, cl_device_id* devices_id, cl_context& context)
{
	cl_int error;
	context = clCreateContext(NULL, n_devices, devices_id, NULL, NULL, &error);
	return error;
}

cl_int CreateCLCommandQueue(const cl_device_id &device_id, const cl_context& context, cl_command_queue &command_queue)
{
	cl_int error;
	command_queue = clCreateCommandQueue(context, device_id, 0, &error);
	return error;
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

cl_int CreateCLKernel(const cl_program& program, const char* kernel_name, cl_kernel& kernel)
{
	cl_int error;
	kernel = clCreateKernel(program, kernel_name, &error);
	return error;
}

cl_int CreateCLBuffer(const cl_context& context, cl_mem_flags flags, size_t size, cl_mem& mem_obj)
{
	cl_int error;
	mem_obj = clCreateBuffer(context, flags, size, NULL, &error);
	return error;
}

cl_int SetCLKernelArgs(const cl_kernel& kernel, cl_uint index, size_t size, const void* value)
{
	return clSetKernelArg(kernel, index, size, value);
}

cl_int CopyCLDataToMemObj(const cl_command_queue& command_queue, cl_mem& buf, cl_bool blocking, size_t size, const void* value)
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
