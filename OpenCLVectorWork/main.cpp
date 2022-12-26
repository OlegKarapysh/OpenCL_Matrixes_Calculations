// OpenCLVectorWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include "DeviceInfo.h"
#include "FileWork.h"
#include "OpenCLwork.h"

typedef float vect_elem_type;
typedef cl_float elem_buf_type;

#define	KERNEL_FILE_NAME	__TEXT("VectorAdd.cl")
#define	KERNEL_NAME			"VectorsAdd"
#define OUT_FILE_NAME		__TEXT("Res.txt")

#define N_ITER				100000

int main()
{
	cl_uint n_platforms, n_devices;
	cl_platform_id* platforms_id = NULL;
	cl_device_id* devices_id = NULL;
	cl_device_type device_type = CL_DEVICE_TYPE_ALL;
	cl_int error_code = 0;
	unsigned char choice = 1;
	unsigned char device_num = 1;

	cl_context context;
	cl_command_queue command_queue;
	char* file_data = NULL;
	DWORD file_size;

	cl_program program;
	cl_kernel kernel;

	cl_mem buf_A, buf_B, buf_Res;
	unsigned vector_size, calc_iter;

	vect_elem_type *A = NULL, *B = NULL, *Res = NULL, value;

// 	Получаем список OpenCL платформ и их кол-во
	if (GetCLPlatformsList(platforms_id, n_platforms))
	{

// Выводим на экран список OpenCL платформ
		OutCLPlatformsInfo(platforms_id, n_platforms);
		
// Выбираем конкретную платформу из списка для последующей работы
		do
		{
			_tprintf(__TEXT("Enter the number of platform to work (from 1 to %u): "), n_platforms);
			choice = _getch();
			putchar(choice);
			putchar('\n');
			choice -= 0x30;
		} while (choice == 0 || choice > n_platforms);

// Получаем список OpenCL устройств и их кол-во для указазанной платформы
		if (GetCLDevicesList(device_type, platforms_id[choice - 1], devices_id, n_devices))
		{

// Выводим на екран список OpenCL устройств для выбранной платформы
			OutCLDevicesInfo(devices_id, n_devices);

// Создаем OpenCL контекст для устройств указанной платформы, для создания в нем объектов, предназначенных для выполнения вычислений.
			if ((error_code = CreateCLContext(n_devices, devices_id, context)) == CL_SUCCESS)
			{

// Если устройств будет более одного, то выбираем номер утсройства для работы
				if (n_devices > 1)
				{
					do
					{
						_tprintf(__TEXT("Enter the number of device to work (from 1 to %u): "), n_devices);
						device_num = _getch();
						putchar(device_num);
						putchar('\n');
						device_num -= 0x30;
					} while (device_num == 0 || device_num > n_devices);
				}

// Создаем очередь команд для выбранного устройства в созданном контексте
				if ((error_code = CreateCLCommandQueue(devices_id[device_num - 1], context, command_queue)) == CL_SUCCESS)
				{

/* 
Считываем из текстового файла исходный код функции ядра (функция, выполняющая заданные расчеты на выбранном устройстве,
описанная с ключевым словом __kernel)
*/

					if (ReadFileToChar((TCHAR*)KERNEL_FILE_NAME, file_data, file_size))
					{
						_tprintf(__TEXT("Kernel text:\n"));
						printf("%s\n\n", file_data);

// На основе прочитанного кода ядра, представленного в виде в строки, создаем объект "программа"
						if ((error_code = CreateCLProgram(context, (const char**)(&file_data), program)) == CL_SUCCESS)
						{

// Создаем исполнимый код ядра (компиляция + линковка)
							if ((error_code = BuildCLProgram(program)) == CL_SUCCESS)
							{

// Создаем объект для ядра
								if ((error_code = CreateCLKernel(program, KERNEL_NAME, kernel)) == CL_SUCCESS)
								{

									_tprintf(__TEXT("Enter the number of vector elements: "));
									_tscanf(__TEXT("%u"), &vector_size);

/*
Создаем 3 объекта для работы с памятью, которые будут использовать для хранения данных 2-ух векторов, а также для хранения результата суммирования.
При этом указываются соответствующие режимы доступа для созданных объектов
*/
									if (((error_code = CreateCLBuffer(context, CL_MEM_READ_ONLY, sizeof(elem_buf_type) * vector_size, buf_A)) == CL_SUCCESS)
										&& (CreateCLBuffer(context, CL_MEM_READ_ONLY, sizeof(elem_buf_type) * vector_size, buf_B) == CL_SUCCESS)
										&& (CreateCLBuffer(context, CL_MEM_WRITE_ONLY, sizeof(elem_buf_type) * vector_size, buf_Res) == CL_SUCCESS))
									{

/*
Устанавливаем соответствующие значения для аргументов функции ядра. В нашем случае это 2 вектора с исходными данными, вектор результата сложения и кол-во
элементов в каждом из векторов
*/
										if ((error_code = SetCLKernelArgs(kernel, 0, sizeof(cl_mem), (void*)(&buf_A))) == CL_SUCCESS
											&& SetCLKernelArgs(kernel, 1, sizeof(cl_mem), (void*)(&buf_B)) == CL_SUCCESS
											&& SetCLKernelArgs(kernel, 2, sizeof(cl_mem), (void*)(&buf_Res)) == CL_SUCCESS
											&& SetCLKernelArgs(kernel, 3, sizeof(cl_uint), (void*)(&vector_size)) == CL_SUCCESS
											)
										{

/*
Выделяем память в приложении под векторы входных данных и вектор результата
*/
											A = (vect_elem_type*)malloc(sizeof(vect_elem_type) * vector_size);
											B = (vect_elem_type*)malloc(sizeof(vect_elem_type) * vector_size);
											Res = (vect_elem_type*)malloc(sizeof(vect_elem_type) * vector_size);

											if (A != NULL && B != NULL && Res != NULL)
											{

// Заполняем векторы входных данных введенным пользователем значением

												_tprintf(__TEXT("Enter value to fill vector elements: "));
												_tscanf(__TEXT("%f"), &value);
												for (unsigned i = 0; i < vector_size; A[i] = B[i] = value, i++);

/*
Копируем данные из исходных векторов A и B в соответствующие объекты памяти, созданные выше, в синхронном режиме
*/
												DWORD time_copy = GetTickCount();
												if ((error_code = CopyCLDataToMemObj(command_queue, buf_A, CL_TRUE, sizeof(elem_buf_type) * vector_size, A)) == CL_SUCCESS
													&& CopyCLDataToMemObj(command_queue, buf_B, CL_TRUE, sizeof(elem_buf_type) * vector_size, B) == CL_SUCCESS
													)
												{

/*
В цикле из указанного цисла итераций (нужно, чтобы получить ненулевое время выполнения) запускаем на выполнение функцию ядра на выбранном OpenCL устройстве
*/
													_tprintf(__TEXT("Starting calculations...\n"));
													DWORD time = GetTickCount();
													for (calc_iter = 0; calc_iter < N_ITER; calc_iter++)
														if ((error_code = RunCLKernel(command_queue, kernel, 1, (size_t*)(&vector_size), NULL)) != CL_SUCCESS)
															break;
													time = GetTickCount() - time;
													_tprintf(__TEXT("The end of calculations.\n"));
													if (calc_iter == N_ITER)
													{												
/*
Считываем данные из обхекта памяти, созданного под помещение в него результата сложения, в выделенный в программе буфер для хранения вектора результатов
*/
														if ((error_code = ReadCLDataFromMemObj(command_queue, buf_Res, CL_TRUE, sizeof(elem_buf_type) * vector_size, Res)) == CL_SUCCESS)
														{
															time_copy = GetTickCount() - time_copy;
/*
Задаем вопрос о необходимости записи полученного результата в файл
*/
															_tprintf(__TEXT("%u interations of calculations have been completed successfully!\n Calculation time is %u ms\n Copying / reading data to / from OpenCL memory objects and calculation time is %u ms\n"), N_ITER, time, time_copy);
															do
															{
																_tprintf(__TEXT("\nDo you want to out resulting data to file (y/n)?"));
																choice = _getch();
																putchar(choice);
															} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

// При соответствующем выборе пользователя записываем элементы результирующего вектора в файл
															if (choice == 'y' || choice == 'Y')
															{
																FILE* F = _tfopen(OUT_FILE_NAME, __TEXT("w+"));
																if (F)
																{
																	fprintf(F, "The list of pairs: vector index - result value:\n");
																	for (unsigned i = 0; i < vector_size; i++)
																		fprintf(F, "%u - %f\n", i, Res[i]);
																}
															}
														}
														else
															_tprintf(__TEXT("Error of data from memory objects reading (error_code = %i)!\n"), error_code);
													}
													else
														_tprintf(__TEXT("Error of kernel running (error_code = %i)!\n"), error_code);
												}
												else
													_tprintf(__TEXT("Error of data to memory objects copying (error_code = %i)!\n"), error_code);
											}

// Освобождение памяти, выделенной под ресурсы
											free(A);
											free(B);
											free(Res);
										}
										else
											_tprintf(__TEXT("Error of kernel arguments setting (error_code = %i)!\n"), error_code);

// Освобождение памяти, выделенной под ресурсы
										clReleaseMemObject(buf_A);
										clReleaseMemObject(buf_B);
										clReleaseMemObject(buf_Res);
									}
									else
										_tprintf(__TEXT("Error of memory objects creating (error_code = %i)!\n"), error_code);

// Освобождение памяти, выделенной под ресурсы
									clReleaseKernel(kernel);
								}
								else
									_tprintf(__TEXT("Error of kernel creating (error_code = %i)!\n"), error_code);
							}
							else
								_tprintf(__TEXT("Error of program building (error_code = %i)!\n"), error_code);

// Освобождение памяти, выделенной под ресурсы
							clReleaseProgram(program);
						}
						else
							_tprintf(__TEXT("Error of program creating (error_code = %i)!\n"), error_code);

// Освобождение памяти, выделенной под ресурсы
						free(file_data);
					}
					else
						_tprintf(__TEXT("Error of file reading %s with kernel source\n"), KERNEL_FILE_NAME);

// Освобождение памяти, выделенной под ресурсы
					clReleaseCommandQueue(command_queue);
				}
				else
					_tprintf(__TEXT("Error of command queue creating (error_code = %i)!\n"), error_code);

// Освобождение памяти, выделенной под ресурсы				
				clReleaseContext(context);
			}
			else
				_tprintf(__TEXT("Error of device context creatring (error_code = %i)!\n"), error_code);

// Освобождение памяти, выделенной под ресурсы
			free(devices_id);
		}

// Освобождение памяти, выделенной под ресурсы
		free(platforms_id);
	}
	return 0;
}

