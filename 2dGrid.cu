// This example demonstrates how to launch two dimensional grids of CUDA
// threads.

#include <stdlib.h>
#include <stdio.h>

__global__ void kernel(int *array) {
  // compute the two dimensional index of this particular
  // thread in the grid
  // do the usual computation separately in each dimension:

  int index_x = blockIdx.x * blockDim.x + threadIdx.x;
  int index_y = blockIdx.y * blockDim.y + threadIdx.y;

  // use the two 2D indices to compute a single linear index
  // fill in grid Dim as I explained in the class

  int grid_width = xxx;

  // index mapps y to a global 1 D
  int index = ;

  // use the two 2D block indices to compute a single linear block index

  int result = blockIdx.y * gridDim.x + blockIdx.x;

  // write out the result
  array[index] = result;
}

int main(void) {

  int num_elements_x = 16;

  int num_elements_y = 16;

  int num_bytes = num_elements_x * num_elements_y * sizeof(int);

  int *device_array = 0;

  int *host_array = 0;

  // malloc a host array

  host_array = (int *)malloc(num_bytes);

  // cudaMalloc a device array

  cudaMalloc((void **)&device_array, num_bytes);

  // if either memory allocation failed, report an error message

  if (host_array == 0 || device_array == 0) {

    printf("couldn't allocate memory\n");

    return 1;
  }

// choose a two dimensional launch configuration

// use the dim3 type when launches are not one dimensional
