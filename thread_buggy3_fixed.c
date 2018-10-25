#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define N 40000

double sum=0.0;
int flag=3;

void *calc(void *rank) {
int *rank_int_ptr = (int*) rank;
int my_rank = *rank_int_ptr;
int my_n = N / NUM_THREADS;
int my_first_i = (my_rank * my_n);
int my_last_i = my_first_i + my_n;

double factor = -1.0;

double sum_local=0.0;

if (my_first_i % 2 == 0) {
factor = 1.0;
}
// use a local sume to avoid serializing every segment and keep other threads as busy
for (int i = my_first_i; i <= my_last_i; i++) {
sum_local += factor / (2*i+1);
factor = -1 * factor;
}


// place busy waiting in here 
//
while (flag != my_rank)
{
// do nothing wait 
 }
sum=sum+sum_local;
printf("my rank %d done with adding, changing the flag %d \n",my_rank, flag );
// note that what we did in the class flag=flag+1 is fine only if the flag starts from the rank 0
// to make it more general such that it works for anyflag I use the remainder operator
flag=(flag+1) % NUM_THREADS;

return NULL;
}


int main() {

pthread_t ids[NUM_THREADS];


int id[NUM_THREADS]={0,1,2,3};

for (int i=0; i < NUM_THREADS; i++) {
pthread_create(&(ids[i]), NULL, calc,&(id[i]));
}


for (int i=0; i < NUM_THREADS; i++) {
pthread_join(ids[i], NULL);
}
printf("pi= %lf\n",sum*4.0);

}

