#include "PlatformInfo.h"

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