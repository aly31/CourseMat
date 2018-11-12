#include "stdio.h"
#include "stdlib.h"
#include <cuda.h>
#include <cuda_runtime.h>


// find two minor bugs in this code

__global__ void mykernel(void) {
printf("Hello World from GPU!\n");
}
int main(void) {

float time;

cudaEvent_t t1, t2;

cudaEventCreate(&t1);
cudaEventCreate(&t2);

// start the timing
cudaEventRecord(t1);

mykernel<<<1,1>>>();

//end timing
cudaEventRecord(t2);

// use this function, do not etract t1 from t2
// time is in milliseconds

cudaEventElapsedTime(&time, t1, t2);

//synch 
cudaEventSynchronize(t2);


cudaDeviceSynchronize();


// what is missig? 

printf("time=%lf milli seconds\n",time);

return 0;
}

