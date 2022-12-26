__kernel void MatrixAdd(
    __global const float* a, 
    __global const float* b, 
    __global float* c, 
    unsigned width,
    unsigned height)
{
  // get index into global data array
  unsigned col = get_global_id(0);
  unsigned row = get_global_id(1); 

  // bound check (equivalent to the limit on a 'for' loop for standard/serial C code
  if (col < width && row < height)
  { 
    i = row * width + col
    c[i] = a[i] + b[i];
  }
  
}