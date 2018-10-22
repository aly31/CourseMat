#include <stdio.h>
#include <pthread.h>

// pthreads: easy condition variable example
#define NTH 4

// notice that the job is performed at most N times, 
//  if you want to get zero water level, user input should be less than
// the number of threads



int water_level = 0;
pthread_mutex_t cond_mutex;
pthread_cond_t cond_var;



void* work(void *custom_data)
{

  pthread_mutex_lock(&cond_mutex);

  while (1)
    {
      // testing the predicate here means that we test it before we wait,
      // AND after we wait. 
      if (water_level > 0)
	{
	  printf("\n Worker thread %d changes water level from %d to %d. \n",pthread_self(),water_level,water_level-1);
	  water_level--;
	}
      else
      {
	  printf("Worker thread %d refuses to work.\n",pthread_self());
      }
      pthread_cond_wait(&cond_var,&cond_mutex);
    }
  
  return(NULL);
}

int main(int argc, char * argv[])
{
  int i;
  pthread_t tID[NTH];
  int uinput;
  
  // initialize the mutex variable and condition variable
  pthread_mutex_init(&cond_mutex,NULL);
  pthread_cond_init(&cond_var,NULL);
  
  // create a batch of worker threads
  for (i = 0; i < NTH; i++)
     pthread_create(&tID[i],NULL,work,NULL);
  
  while(1)
    {
      printf("User input water level change: "); scanf("%d",&uinput);
      if (uinput != 0)
	{
	  pthread_mutex_lock(&cond_mutex);
	  water_level += uinput;
	  pthread_mutex_unlock(&cond_mutex);

	  pthread_cond_broadcast(&cond_var);
	}
    } 

  for (i = 0; i < 5; i++)
    pthread_join(tID[i],NULL);
  
  pthread_mutex_destroy(&cond_mutex);
  pthread_cond_destroy(&cond_var);
  
  return(0);
}


