#include <stdio.h>
#include <stdlib.h>

// use  valgrind to find a problem here

int main(int argc, char * argv[])
{
  int i;
  int *a_heap = NULL;
  int a_stack[10];

  a_heap = (int*)malloc(10*sizeof(int));
  
  for (i = 0; i < 10; ++i)
  {
    a_heap[i] = i;
    a_stack[i] = i;
  }

  for (i = 0; i <= 10; ++i)
  {
    printf("A = %d (stack) %d (heap) \n",a_heap[i],a_stack[i]);
  }

  free(a_heap);


  return(0);

}

