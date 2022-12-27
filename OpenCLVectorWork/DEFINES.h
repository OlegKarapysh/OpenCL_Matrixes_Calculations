#pragma once
#include <CL/cl.h>
//#define DOUBLE
#define FLOAT

#define	KERNEL_FILE_NAME	__TEXT("VectorAdd.cl")
#define	KERNEL_NAME			"VectorsAdd"
#define FILL_FIXED          2
#define FIXED_NUM           5.5f

#ifdef FLOAT
typedef float INF;
typedef cl_float INF_BUFFER;
#define	KERNEL_FILE_NAME	__TEXT("VectorAdd_float.cl")
#endif // FLOAT

#ifdef DOUBLE
typedef double inf;
typedef cl_double inf_buffer;
#define	KERNEL_FILE_NAME	__TEXT("VectorAdd_double.cl")
#endif // DOUBLE