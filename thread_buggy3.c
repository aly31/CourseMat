#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define N 40000

double sum=0.0;
int flag=0;

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

for (int i = my_first_i; i <= my_last_i; i++) {
sum_local += factor / (2*i+1);
factor = -1 * factor;
}

// place busy waiting in here 
printf("my rank %d done with adding, changing the flag\n",my_rank );


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

}

