#include <stdio.h>
#include <pthread.h>

// average ten numbers
// pthreads example with a mutex

double list[10] = {3.0,2.5,2.2,1.0,5.6,4.5,3.2,3.1,1.7,1.9};

double global_sum = 0.0;
pthread_mutex_t global_sum_mutex;

void* accumulate(void *custom_data)
{
  int i;
  double sum = 0.0;
  int indx = *((int*)custom_data);
  for (i = 5*indx; i < 5*indx + 5; i++) 
    {
      sum += list[i];
    }

  global_sum += sum;

  return(NULL);
}


int main(int argc, char * argv[])
{
  pthread_t tID[2];
  int indx[2];
  int i;

  // initialize the mutex variable
  pthread_mutex_init(&global_sum_mutex,NULL);

  // create the threads
  for (i = 0; i < 2; i++)
    {
      indx[i] = i;
      pthread_create(&tID[i],NULL,accumulate,&indx[i]);
    }
  
  // suspend the execution of the calling thread until threads one and
  // two terminate
  for (i = 0; i < 2; i++)
    {
      pthread_join(tID[i],NULL);
    }

  //sleep(1);

  printf("Pthreads: the average was computed as %.4lf\n",global_sum/10.0);

  pthread_mutex_destroy(&global_sum_mutex);
  
  return(0);
}

