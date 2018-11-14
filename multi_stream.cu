#include "stdlib.h"
#include "stdio.h"

//  nvprof --print-gpu-trace ./myEx (0 or 1) 
//  see the kernel launch time
//  Modified from NVIDIA example to illustrate streams 
// enter 0 and run
// enter 1 and run again
// compare the start times for the two kernels

const int N=1 << 26;

__global__ void kernel1(float *x, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    for (int i = tid; i < n; i += blockDim.x * gridDim.x) {
        x[i] = sqrt(pow(3.14159,i));
    }
}

__global__ void kernel2(float *x, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    for (int i = tid; i < n; i += blockDim.x * gridDim.x) {
        x[i] = sqrt(pow(1.2,i));
    }
}

int main(int argc, char *argv[])
{
    const int num_streams = 2;
    printf(" N =% d\n",N);

    cudaStream_t streams[num_streams];
    float *data[num_streams];


   if(argc!=2)
   {
   printf("enter 0 for default tream and 1 for multi stream as command line arg\n");
   exit(1);
}

   int bol=atoi(argv[1]);

    for (int i = 0; i < num_streams; i++) {

        cudaStreamCreate(&streams[i]);

        cudaMalloc(&data[i], N * sizeof(float));

    }


if(bol==0)
{
        cudaMalloc(&data[0], N * sizeof(float));
        kernel1<<<1, 64, 0>>>(data[0], N);
        cudaMalloc(&data[1], N * sizeof(float));
        kernel2<<<1, 64, 0>>>(data[1], N);

 }
else
{
        kernel1<<<1, 64, 0, streams[0]>>>(data[0], N);
         kernel2<<<1, 64, 0, streams[1]>>>(data[1], N);

}




    cudaDeviceReset();

    return 0;
}


