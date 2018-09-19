#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <mpi.h>

 #define RED "\033[01;31m"
 #define RESET "\033[22;0m"

// MPI_Barrier()
// example of collective synchronization

char * timestamp()
{
  time_t a = time(NULL);
  return ctime(&a);
}

int main (int argc, char* argv[])
{
  int my_rank,np;
  double a;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  printf("Process %d before work at %s",my_rank,timestamp());

  if (my_rank == (np - 1))
    {  
      // do some work that takes time for some people sleeping is work too :-) 
      sleep(5.0);
    }

// coment and then uncomment and run
//  MPI_Barrier(MPI_COMM_WORLD);

  printf(RED"Process %d after barrier at %s" RESET,my_rank,timestamp());

  MPI_Finalize();
  return(0);
}

