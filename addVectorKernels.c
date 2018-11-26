#include "stdio.h"
#include "stdlib.h"
#include "openacc.h"
#include <math.h>

int main(int argc, char *argv[]) {
  // Size of vectors
  int n = 100000;

  // Host input vectors
  double *a = NULL;
  double *b = NULL;
  // Host output vector
  double *c = NULL;

  size_t bytes = n * sizeof(double);

  // Allocate memory for each vector on host
  a = (double *)malloc(n * sizeof(double));
  b = (double *)malloc(n * sizeof(double));
  c = (double *)malloc(n * sizeof(double));


  int i;
  // Initialize vectors on host

  double sum = 0;

// use kernels to parallelize 

  for (i = 0; i < n; i++) {
    a[i] = sin(i) * sin(i);
   b[i] = cos(i) * cos(i);
  }
for(int i=0;i<n;i++)
{
c[i]=a[i]+b[i];
}

  // Sum up vector c and print result divided by n, this should equal 1 within
  // error
  for (i = 0; i < n; i++)
    sum += c[i];

  printf("final result: %f\n", sum / n);

  // Release host memory
  free(a);
  free(b);
  free(c);

  return 0;
}
