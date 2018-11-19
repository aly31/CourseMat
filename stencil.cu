/*
Program: addVector

A basic C/CUDA code to get started with GPU computing
The program check for GPUs on the host, prints some of the specifications
of the GPU, and then set a GPU with certain specs for computation. The CUDA
kernel illustrates allocating memory on the device, copying data to the device
and then doing a simple addition on the GPU and copying the results back to the
host and finally freeing the memory on the device.

Author: Inanc Senocak

to compile: nvcc -O2 addVectorCUDA.cu -o run.exe
to execute: ./run.exe

Demonstrate stack vs. heap memory by making NX small and large values

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#define BLOCKSIZE 256
#define RADIUS 3
#define NX 10000000 // make NX a large number to test stack vs. heap
#define LINSIZE BLOCKSIZE + 2 * RADIUS

/* The argument now should be a double (not a pointer to a double) */
#define GET_TIME(now)                                                          \
  {                                                                            \
    struct timeval t;                                                          \
    gettimeofday(&t, NULL);                                                    \
    now = t.tv_sec + t.tv_usec / 1000000.0;                                    \
  }

typedef float REAL;
__global__ void stencil_1d(int *in, int *out) {
  __shared__ int temp[LINSIZE];

  int gindex = threadIdx.x + blockIdx.x * blockDim.x;
  int lindex = threadIdx.x + RADIUS;

  // Read input elements into shared memory

  temp[lindex] = in[gindex];
  __syncthreads();

  // Apply the stencil
  int result = 0;
  for (int offset = -RADIUS; offset <= RADIUS; offset++)
    result += temp[lindex + offset];

  // Store the result
  out[gindex] = result;
}

// stencil for CPU
void cpu_stencil(int *in, int *out) {
  for (int i = RADIUS; i < NX; i++) {
    REAL sum = 0.0f;
    for (int j = -RADIUS; j <= RADIUS; j++) {
      sum += in[i + j];
    }
    out[i] = sum;
  }
}
int main(void) {
  /*
    // let's see how many CUDA capable GPUs we have

    int gpuCount;

    cudaGetDeviceCount(&gpuCount);

    printf(" Number of GPUs = %d\n", gpuCount);

    int myDevice = 0;

    cudaSetDevice(myDevice);
  */

  // let's use the device to do some calculations
  //  int a[NX],b[NX],c[NX];
  /*
    int *a = malloc(NX * sizeof(*a));
    int *b = malloc(NX * sizeof(*b));
    int *c = malloc(NX * sizeof(*c));
  */
  int *a = (int *)malloc(NX * sizeof(*a));
  int *b = (int *)malloc(NX * sizeof(*b));
  int *c = (int *)malloc(NX * sizeof(*c));

  int *d_a, *d_b, *d_c; // create pointers for the device

  cudaMallocManaged(&d_a, NX * sizeof(int)); // attach d_ to varibles
  cudaMallocManaged(&d_b, NX * sizeof(int));
  cudaMallocManaged(&d_c, NX * sizeof(int));

  // Let's fill the arrays with some numbers

  for (int i = 0; i < NX; i++) {
    a[i] = 4;
    b[i] = 0;
    c[i] = 0;
  }

  // Let's create the infrastructure to time the host & device operations

  double start, finish; // for the CPU

  cudaEvent_t timeStart,
      timeStop; // WARNING!!! use events only to time the device
  cudaEventCreate(&timeStart);
  cudaEventCreate(&timeStop);
  float elapsedTime; // make sure it is of type float, precision is
                     // milliseconds (ms) !!!

  GET_TIME(start);
  // Let's do the following operation on the arrays on the host: a = b +
  // c
  cpu_stencil(a, b);

  GET_TIME(finish);

  printf("elapsed wall time (host) = %.6f seconds\n", finish - start);

  // Let's print the results on the screen

  printf("b, c, a=b+c\n");

  //     for (int i=0; i<NX; i++) {
  //         printf("%d %2d %3d\n", b[i], c[i], a[i]);
  //     }

  cudaMemcpy(d_a, a, NX * sizeof(float),
             cudaMemcpyHostToDevice); // memcpy(dest,src,...

  cudaEventRecord(timeStart, 0); // don't worry for the 2nd argument zero, it is
                                 /*                    // about cuda streams

    dim3 threadsPerBlock(16,
                         16); // Best practice of having 256 threads per block
    dim3 numBlocks((NX + threadsPerBlock.x - 1) / threadsPerBlock.x,
                   (NY + threadsPerBlock.y - 1) / threadsPerBlock.y);
  */
  int nBlocks = (NX + BLOCKSIZE - 1) / BLOCKSIZE; // round up if n
  stencil_1d << <nBlocks, BLOCKSIZE>>>
      (d_a, d_b); // Be careful with the syntax!

  //*/
  /*     int blockSize = 256;
       int nBlocks   = (NX + blockSize -1) / blockSize; //round up if n
     is not a multiple of blocksize myKernel <<<nBlocks,
     blockSize>>>(d_a, d_b, d_c);
       //myKernel<<<1, 1>>> (d_a, d_b, d_c);*/

  printf("a[100] = %4d\n", a[100]);

  cudaEventRecord(timeStop, 0);
  cudaEventSynchronize(timeStop);

  // WARNING!!! do not simply print (timeStop-timeStart)!!

  cudaEventElapsedTime(&elapsedTime, timeStart, timeStop);

  printf("elapsed wall time (device) = %3.1f ms\n", elapsedTime);

  cudaEventDestroy(timeStart);
  cudaEventDestroy(timeStop);

  cudaMemcpy(c, d_b, NX * sizeof(float), cudaMemcpyDeviceToHost);

  //     for (int i=0; i<NX; i++) {
  //         printf("%3d\n", a[i]);
  //     }

  cudaFree(d_a);
  cudaFree(d_b);
  free(a);
  free(b);
  free(c);
  return EXIT_SUCCESS;
}
