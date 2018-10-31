#include <stdio.h>
#include <omp.h>

// OpenMP example
// simple for workshare example

int main(int argc, char * argv[])
{
  int i;

  omp_set_num_threads(4);
  
#pragma omp parallel 
  {
#pragma omp for schedule(dynamic,50)
    for (i = 0; i < 200; i++)
    { 
      printf("My thread ID is %d [doing loop iteration %d]\n",omp_get_thread_num(),i); 
      sleep(0.006*i); // simulates doing work whose length depends on i
    }
  }
  
  return(0);
}


