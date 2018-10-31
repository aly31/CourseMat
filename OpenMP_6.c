#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


// data environment example
// OpenMP example
// firstprivate sample


int main(int argc, char * argv[])
{
  int i = 557;

  omp_set_num_threads(atoi(argv[1]));
  
#pragma omp parallel default(none) private(i) 
  {
   i += omp_get_thread_num() + 1 ;
   printf("Within thread %d, i = %d\n",omp_get_thread_num(),i);
  }

  printf("In main thread, i = %d\n",i);
  

  
  return(0);
}

