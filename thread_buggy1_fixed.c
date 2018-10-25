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



int id[N]={0,1,2,3};

for (int i=0; i < N; i++) {
pthread_create(&ids[i], NULL, hello,&(id[i]));
}


for (int i=0; i < N; i++) {
pthread_join(ids[i], NULL);
}

}




