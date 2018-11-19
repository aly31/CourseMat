#include "stdlib.h"
#include "stdio.h"

__global__ void add(int a, int b, int *c) { *c = a + b; }

int main() {
  int c;
  int *d_c;

  cudaMalloc((void **)&d_c, sizeof(int));

  add << <1, 1>>> (3, 5, d_c);

  cudaMemcpy(&c, d_c, sizeof(int), cudaMemcpyDeviceToHost);

  printf("result is  %d\n", c);

  cudaFree(d_c);
}
