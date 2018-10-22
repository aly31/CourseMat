#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



int global_var1=5;
int global_var2=10;

pthread_mutex_t mutex;



void* my_thread(void *custom_data)
 {
   // any variables I declare here will reside on the stack associated with
   // the thread running this routine.

   int local1=global_var1;
   int local2=global_var2;
   printf("%d %d %d\n",pthread_self(),local1, local2);
 
   // I can call other functions with no problem, but just make sure that 
   // they are thread safe.  It is possible that other threads will execute
   // that function too, concurrently.
//   do_work();
 sleep(1);
   return(NULL);
 }


int main()
{


 pthread_t t1;
 pthread_t t2;
 
   // create the thread
 pthread_create(&t1,NULL,my_thread,NULL);
 pthread_create(&t2,NULL,my_thread,NULL);

 global_var1=1;

pthread_join(t2,NULL);

pthread_join(t1,NULL);

}

 



