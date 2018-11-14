#include "stdio.h"
#include "stdlib.h"


__global__ void vecAdd(double *a, double *b, double *c, int n)

{
    // Get our global thread ID
    int id = blockIdx.x*blockDim.x+threadIdx.x;

    // Make sure we do not go out of bounds
    if (id < n) 
        c[id] = a[id] + b[id];
}


int main( int argc, char* argv[] )
{
    // Size of vectors
    int n = 100000;

    // Host input vectors
    double *a=NULL;
    double *b=NULL;
    //Host output vector
    double *c=NULL;

    // Device input vectors
    double *d_a=NULL;
    double *d_b=NULL;
    //Device output vector
    double *d_c=NULL;

    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(double);

    // Allocate memory for each vector on host
    a = (double*)malloc(n*sizeof(double));
    b = (double*)malloc(n*sizeof(double));
    c = (double*)malloc(n*sizeof(double));

    // Allocate memory for each vector on GPU, including d_a, d_b and d_c
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);


    int i;
    // Initialize vectors on host
    for( i = 0; i < n; i++ ) {
        a[i] = sin(i)*sin(i);
        b[i] = cos(i)*cos(i);
    }

    // Copy host vectors to device
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
   cudaMemcpy( d_a, a, n*sizeof(double), cudaMemcpyHostToDevice);
   cudaMemcpy( d_b, b, n*sizeof(double), cudaMemcpyHostToDevice);
 

    int blockSize, gridSize;

    // Number of threads in each thread block
    blockSize = 1024;

    // Number of thread blocks in grid
    gridSize = (int)ceil((float)n/blockSize);

    // Execute the kernel
    vecAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

    // Copy array back to host
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
     cudaMemcpy( c, d_c, bytes, cudaMemcpyDeviceToHost );
    // Sum up vector c and print result divided by n, this should equal 1 within error
    double sum = 0;
 for(i=0; i<n; i++)
        sum += c[i];
    printf("final result: %f\n", sum/n);

    // Release device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // Release host memory
    free(a);
    free(b);
    free(c);

    return 0;
}

