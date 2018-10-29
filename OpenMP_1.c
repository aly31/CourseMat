#include <stdio.h>
#include <omp.h>

// simplest OpenMP example
// OpenMP example
// should have a critical section, but we will cover that issue later.

int main(int argc, char * argv[])
{
  omp_set_num_threads(4);
  
#pragma omp parallel 
  {   
    printf("My thread ID is: %d\n",omp_get_thread_num());   
  }
  
  return(0);
}


