#include <stdio.h>
#include <pthread.h>

// average ten numbers
// pthreads example

double list[10] = {3.0,2.5,2.2,1.0,5.6,4.5,3.2,3.1,1.7,1.9};

void* my_thread1(void *custom_data)
{
  int i;
  double *sum = (double*)custom_data;
  for (i = 0; i < 5; i++) 
  {
     (*sum) = (*sum) + list[i];
     printf("sum = %.4f thread = %d\n",*sum,0);
  }
  return(NULL);
}

void* my_thread2(void *custom_data)
{
  int i;
  double *sum = (double*)custom_data;
  for (i = 5; i < 10; i++) 
  {
	  (*sum) = (*sum) +  list[i];
	  printf("sum = %.4f thread = %d\n",*sum,1);
  }
  return(NULL);
}

int main(int argc, char * argv[])
{

  pthread_t t1;
  pthread_t t2;
  double sum1 = 0.0, sum2 = 0.0;

  // create the threads
  pthread_create(&t1,NULL,my_thread1,&sum1);
  pthread_create(&t2,NULL,my_thread2,&sum2);
  
  // suspend the execution of the calling thread until threads one and
  // two terminate
  pthread_join(t2,NULL);
  pthread_join(t1,NULL);

  printf("Pthreads: the average was computed as %.4lf\n",(sum1 + sum2)/10.0);
  
  return(0);
}

