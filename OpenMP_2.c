 #include <stdio.h>
#include <omp.h>

// simplest OpenMP example
// OpenMP example
// will determine the number of threads from the environment 
// variable OMP_NUM_THREADS

int main(int argc, char * argv[])
{
#pragma omp parallel 
  {
    printf("My thread ID is: %d\n",omp_get_thread_num());   
  }
  
  return(0);
}


