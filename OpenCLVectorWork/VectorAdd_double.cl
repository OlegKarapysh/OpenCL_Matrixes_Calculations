__kernel void VectorsAdd(
  __global const double* a, 
  __global const double* b, 
  __global const double* c, 
  __global const double* d, 
  __global const double* e, 
  __global const double* f,
  __global double* res, 
  unsigned size)
{
  // get index into global data array
  int GID = get_global_id(0);

  // bound check (equivalent to the limit on a 'for' loop for standard/serial C code
  if (GID < size)
  { 
    res[GID] = a[GID] + b[GID] * c[GID] - d[GID] - e[GID] - f[GID];
  }
  
}