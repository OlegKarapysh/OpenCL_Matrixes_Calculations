__kernel void VectorsAdd(
  __global const float* a, 
  __global const float* b, 
  __global const float* c, 
  __global const float* d, 
  __global const float* e, 
  __global const float* f, 
  __global float* res, 
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