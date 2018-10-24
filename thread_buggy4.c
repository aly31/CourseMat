#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

int counter=0;

pthread_mutex_t sync_mutex = PTHREAD_MUTEX_INITIALIZER;


int do_work(void);

void *create(void *custom_data)
{
  int *my_rank=(int*)custom_data;

// 
// put the barrier in here 
//


  return(NULL);
}




int main() {

pthread_t ids[NUM_THREADS];


int id[NUM_THREADS]={0,1,2,3};

for (int i=0; i < NUM_THREADS; i++) {
pthread_create(&(ids[i]), NULL, create,&(id[i]));
}


for (int i=0; i < NUM_THREADS; i++) {
pthread_join(ids[i], NULL);
}


}




