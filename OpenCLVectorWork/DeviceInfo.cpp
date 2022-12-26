#include "DeviceInfo.h"

bool GetCLDevicesList(const cl_device_type& device_type, const cl_platform_id& platform_id, cl_device_id*& devices_id, cl_uint& n_devices)
{
	return (clGetDeviceIDs(platform_id, device_type, NULL, NULL, &n_devices) == CL_SUCCESS) &&
		((devices_id = (cl_device_id*)malloc(n_devices * sizeof(cl_device_id))) != NULL)
		&& (clGetDeviceIDs(platform_id, device_type, n_devices, devices_id, NULL) == CL_SUCCESS);
}

bool GetCLPlatformsList(cl_platform_id*& platforms_id, cl_uint& n_platforms)
{
	if (clGetPlatformIDs(NULL, NULL, &n_platforms) == CL_SUCCESS)
	{
		platforms_id = (cl_platform_id*)malloc(n_platforms * sizeof(cl_platform_id));
		return ((platforms_id) && clGetPlatformIDs(n_platforms, platforms_id, NULL) == CL_SUCCESS);
	}
	return false;
}


void OutCLPlatformsInfo(cl_platform_id* platforms_id, const cl_uint& n_platforms)
{
	const cl_platform_info PlAttrTypes[] = 
	{
		CL_PLATFORM_NAME,
		CL_PLATFORM_VENDOR,
		CL_PLATFORM_VERSION,
		CL_PLATFORM_PROFILE,
		CL_PLATFORM_EXTENSIONS
	};
	const TCHAR* PlAttrNames[] = 
	{ 
		__TEXT("Name"), 
		__TEXT("Vendor"), 
		__TEXT("Version"),
		__TEXT("Profile"),
		__TEXT("Extensions") 
	};

	void* tmp, * param_value = NULL;
	size_t size;

	for (cl_uint i = 0; i < n_platforms; i++)
	{
		_tprintf(__TEXT("\n\nPlatform %u info:\n"), i + 1);
		for (int j = 0; j < sizeof(PlAttrNames); j++)
			if (clGetPlatformInfo(platforms_id[i], PlAttrTypes[j], NULL, NULL, &size) == CL_SUCCESS)
			{
				tmp = realloc(param_value, size + 1);
				if (tmp)
				{
					param_value = tmp;
					if (clGetPlatformInfo(platforms_id[i], PlAttrTypes[j], size, param_value, NULL) == CL_SUCCESS)
					{
						_tprintf(__TEXT(" Platform %s: "), PlAttrNames[j]);
						puts((char*)param_value);
					}
				}
			}
	}
	putchar('\n');
	putchar('\n');
}

void OutCLDevicesInfo(cl_device_id* devices_id, const cl_uint& n_devices)
{
	const cl_device_info DevAttrTypesChar[] = 
	{
		CL_DEVICE_NAME,
		CL_DEVICE_VENDOR,
		CL_DEVICE_VERSION,
		CL_DRIVER_VERSION,
		CL_DEVICE_EXTENSIONS
	};

	const TCHAR* DevAttrNamesChar[] = 
	{ 
		__TEXT("Name"), 
		__TEXT("Vendor"),
		__TEXT("Device Version"), 
		__TEXT("Driver Version"),
		__TEXT("Extensions") 
	};

	const cl_device_info DevAttrTypesUINT[] = 
	{
		CL_DEVICE_MAX_CLOCK_FREQUENCY,
		CL_DEVICE_MAX_COMPUTE_UNITS,
		CL_DEVICE_MAX_SAMPLERS,
		CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
	};

	const cl_device_info DevAttrTypesULONG[] = 
	{
		CL_DEVICE_GLOBAL_MEM_SIZE,
		CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
		CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
		CL_DEVICE_MAX_MEM_ALLOC_SIZE
	};

	const cl_device_info DevAttrTypesSIZE_T[] = 
	{
		CL_DEVICE_MAX_PARAMETER_SIZE,
		CL_DEVICE_MAX_WORK_GROUP_SIZE
	};

	const TCHAR* DevAttrNamesUINT[] = 
	{ 
		__TEXT("Maximal frequency (MHz)"), 
		__TEXT("Maximal compute units number"),
		__TEXT("Maximal number of samplers that can be used in kernel"),
		__TEXT("Maximum dimensions that specify the global and local work-item IDs used by the data parallel execution mode")
	};
	const TCHAR* DevAttrNamesULONG[] = 
	{ 
		__TEXT("Global memory size (bytes)"),
		__TEXT("Global memory cache size (bytes)"),
		__TEXT("Maximal size of constant buffer allocation (bytes)"),
		__TEXT("Maximal size of memory object allocation (bytes)"),
	};

	const TCHAR* DevAttrNamesSIZE_T[] = 
	{ 
		__TEXT("Maximal size of arguments that can be passed to kernel (bytes)"),
		__TEXT("Maximal number of work-items in a work-group executing a kernel using the data parallel execution model")
	};


	void* tmp, * param_value = NULL;
	size_t size;
	cl_uint value_uint;
	cl_ulong value_ulong;
	size_t value_size_t;
	cl_device_type device_type;


	for (cl_uint i_dev = 0; i_dev < n_devices; i_dev++)
	{
		if (clGetDeviceInfo(devices_id[i_dev], CL_DEVICE_TYPE, sizeof(cl_device_type), (void*)(&device_type), NULL) == CL_SUCCESS)
		{
			_tprintf(__TEXT("Type of %u device is %s\n"), i_dev + 1,
				device_type & CL_DEVICE_TYPE_GPU ? __TEXT("GPU") : device_type & CL_DEVICE_TYPE_CPU ? __TEXT("CPU")
				: device_type & CL_DEVICE_TYPE_ACCELERATOR ? __TEXT("ACCELERATOR") : __TEXT("DEFAULT"));
		}

		for (int j = 0; j < sizeof(DevAttrNamesChar); j++)
			if (clGetDeviceInfo(devices_id[i_dev], DevAttrTypesChar[j], NULL, NULL, &size) == CL_SUCCESS)
			{
				tmp = realloc(param_value, size + 1);
				if (tmp)
				{
					param_value = tmp;
					if (clGetDeviceInfo(devices_id[i_dev], DevAttrTypesChar[j], size, param_value, NULL) == CL_SUCCESS)
					{
						_tprintf(__TEXT(" %s: "), DevAttrNamesChar[j]);
						puts((char*)param_value);
					}
				}
			}
		putchar('\n');
		for (int j = 0; j < sizeof(DevAttrNamesUINT); j++)
			if (clGetDeviceInfo(devices_id[i_dev], DevAttrTypesUINT[j], sizeof(value_uint), (void*)(&value_uint), NULL) == CL_SUCCESS)
				_tprintf(__TEXT(" %s: %u\n"), DevAttrNamesUINT[j], value_uint);

		for (int j = 0; j < sizeof(DevAttrNamesULONG); j++)
			if (clGetDeviceInfo(devices_id[i_dev], DevAttrTypesULONG[j], sizeof(value_ulong), (void*)(&value_ulong), NULL) == CL_SUCCESS)
				_tprintf(__TEXT(" %s: %I64u\n"), DevAttrNamesULONG[j], value_ulong);

		for (int j = 0; j < sizeof(DevAttrNamesSIZE_T) / sizeof(size_t); j++)
			if (clGetDeviceInfo(devices_id[i_dev], DevAttrTypesSIZE_T[j], sizeof(size_t), (void*)(&value_size_t), NULL) == CL_SUCCESS)
				_tprintf(__TEXT(" %s: %zu\n"), DevAttrNamesSIZE_T[j], value_size_t);

		putchar('\n');
		putchar('\n');
	}
}