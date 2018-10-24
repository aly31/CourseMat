#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 4


void *hello (void *rank) {
int *rank_int_ptr = (int*) rank;
printf("Hello Thread %d\n", *rank_int_ptr);
fflush(stdout);
}


int main() {

pthread_t ids[N];



int id[3]={0,1,2};

for (int i=0; i < N; i++) {
pthread_create(&ids[i], NULL, hello,&i);
}





}




