#include <stdio.h>
#include <omp.h>

// average ten numbers
// OpenMP example

int main(int argc, char * argv[])
{
  double list[10] = {3.0,2.5,2.2,1.0,5.6,4.5,3.2,3.1,1.7,1.9};
  double sum = 0.0;
  int i;

  omp_set_num_threads(2);
  
 
  {
#pragma omp for 
   for (i = 0; i < 10; i++)
     {
#pragma omp critical
	     {
       		sum += list[i];
		printf("Thread %d is adding %f (entry %d) to the sum = %f\n",omp_get_thread_num(),list[i],i,sum);
	     }
     }
  }
  

  printf("OpenMP: the average was computed as %.4lf\n",sum/10.0);
  
  return(0);
}


