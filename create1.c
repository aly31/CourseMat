#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int do_work(void);

void* my_thread(void *custom_data)
{
  // any variables I declare here will reside on the stack associated with
  // the thread running this routine.

  // I can call other functions with no problem, but just make sure that 
  // they are thread safe.  It is possible that other threads will execute
  // that function too, concurrently.
  do_work();
  return(NULL);
}

int do_work(void)
{
  printf("I am a thread doing my work.\n");
  sleep(3);
  printf("Done.\n");
  return(0);
}

int main(int argc, char * argv[])
{
  pthread_t t1;

  // create the thread
  pthread_create(&t1,NULL,my_thread,NULL);
  
  // suspend the execution of the calling thread (meaning, this thread) 
  // until the thread we spawned terminates 
  pthread_join(t1,NULL);
 
  printf("Now, I'm back in the main thread, about to return.\n");
 
  return(0);
}
