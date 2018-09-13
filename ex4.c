#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define RED "\033[01;31m"
#define RESET "\033[22;0m"

// average ten numbers
// this sample is designed to run with two processes

int main (int argc, char* argv[])
{
  int my_rank,len,np,i;
  double sum0 = 0.0;
  double sum1;
  char pname[256];
  MPI_Status status;

  // note that we are being inefficient here, since we store all of the
  // data on all processes.  This is to keep the example simple!
  double list[10] = {3.0,2.5,2.2,1.0,5.6,4.5,3.2,3.1,1.7,1.9};

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);
  MPI_Get_processor_name(pname,&len);

  printf("PROCESS %d of %d: Running on %s\n",my_rank+1,np,pname);

  if (np != 2)
    {
      printf("This code is designed for two processes only!\n");
      MPI_Finalize();
      exit(1);
    }

  // add up the appropriate range of numbers in our list
  for (i = 0; i < 5; i++) sum0 += list[my_rank*5 + i];

  if (my_rank == 0)
    {
      MPI_Recv(&sum1, 1, MPI_DOUBLE, 1 , 0, MPI_COMM_WORLD, &status);
      sum0 += sum1;
      printf(RED"The host process reports an average of %.4lf\n"RESET,sum0/10.0);
    }
  else
    {
      MPI_Send(&sum0, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    }



  MPI_Finalize();
 return(0);
}


