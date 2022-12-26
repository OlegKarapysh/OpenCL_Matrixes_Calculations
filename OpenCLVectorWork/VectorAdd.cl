__kernel void VectorsAdd(__global const float* a, __global const float* b, __global float* c, unsigned iNumElements)
{
  // get index into global data array
  int iGID = get_global_id(0);

  // bound check (equivalent to the limit on a 'for' loop for standard/serial C code
  if (iGID < iNumElements)
  { 
    c[iGID] = a[iGID] + b[iGID];
  }
  
}