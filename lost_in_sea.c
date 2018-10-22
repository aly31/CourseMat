
//////////////////////////////////////////////////////////
//
// This code implements a limited lost-at-sea analogy.  In
// this code, one person grabs for the oars first, and does
// the rowing/monitoring for the duration of the trip.  The
// other two people sleep unless they are woken by the
// rower with a shout.  Then, one or the other bails until
// the water level is permissible, then falls back asleep.
//
//////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// global variables.  These are created on the heap, and as such, have a
// lifetime equal to the life of the program.  They are also visible to
// all threads.

// shared data
double water_level = 6.0;
double critical_water_level = 12.0;
double ok_water_level = 9.0;

// mutexes
pthread_mutex_t oars = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bucket = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t water_level_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t shout = PTHREAD_COND_INITIALIZER;


void row(int ID)
{
  int retval;

  printf("Person %d begins to row.\n",ID);

  while(1)
    {
      sleep(1);

      // while rowing, we constantly monitor the water level
      if (water_level > critical_water_level)
	{
 	  // check to see if the bucket is in use; we don't bother
	  // shouting unless no one is bailing.
          // if someone has the bucket that means he is or about to bail
	  retval = pthread_mutex_trylock(&bucket);
	  if (retval == 0)
	    {
	      // broadcast a signal that someone needs to start bailing!!
	      printf("Person %d: HEY!!! We are about to sink!\n",ID);
	      pthread_mutex_unlock(&bucket); 
	      pthread_cond_broadcast(&shout);
	    }
	}

      //if (im_tired)
      //{
      //  pthread_mutex_unlock(oars);
      //  return;
      //}
    }


}


// actual bailing 
void bail_water(int ID)
{
  printf("Person %d starts bailing.\n",ID);

  int is_ok;

  while(1)
    {
      // we can bail at 1.5 inches per second
      pthread_mutex_lock(&water_level_mutex);
      water_level -= 1.5;
      is_ok = water_level < ok_water_level;
      pthread_mutex_unlock(&water_level_mutex);

      if (is_ok) 
	{
	  return;
	}
      
      sleep(1); 
    }
}


// need to get the bucket, check the conditon, depending on the condition either bail or sleep
void non_rower(int ID)
{
   pthread_mutex_lock(&bucket);
   printf("Person %d picks up the bucket. \n",ID);

   while(1)
   {
     if (water_level > critical_water_level)
       {
         bail_water(ID);
       }
     else
       {
          printf("Person %d sees that there is no need to bail.\n",ID);
      }

     printf("Person %d goes to sleep. Zzzzzzz.....\n",ID);
     pthread_cond_wait(&shout,&bucket);
 
     printf("Person %d wakes up, bucket in hand. \n",ID);
   }
}

// one thread becomes rower and the other two become bailer/sleeper
void* person_routine(void * pointer_to_id)
{
  int retval;
  int ID = *(int*)pointer_to_id;

 
  // the first thing that we try to do is grab the oars and start rowing.
  retval = pthread_mutex_trylock(&oars);
  
  if (retval == 0)
    {
      // we successfully took the oars.  Start rowing.
      row(ID);
    }
  else
    {
      // if we didn't get the oars, we go into an infinite cycle
      // of bailing water when necessary and sleeping.
      non_rower(ID);
    }    
  
  return(NULL);
}


int main (int argc, char * argv[])
{
  pthread_t person1,person2,person3;
  int ID1=1,ID2=2,ID3=3;

  pthread_create(&person1,NULL,person_routine,&ID1);
  pthread_create(&person2,NULL,person_routine,&ID2);
  pthread_create(&person3,NULL,person_routine,&ID3);


  // 
  // now, we go into an infinite loop that increases the
  // water level
  //
  while(1)
    {
      // water level goes up 1.25 inch per second
      sleep(1);
      printf("Water level: %lf\n",water_level);
      pthread_mutex_lock(&water_level_mutex);
      water_level += 1.25;
      pthread_mutex_unlock(&water_level_mutex);
    }

  pthread_join(person1,NULL);
  pthread_join(person2,NULL);
  pthread_join(person3,NULL);

  return(0);
}

