#include <stdio.h>
#include <mpi.h>

// MPI_Scatter()
// example of scatter data
//  scatter data from the root process to other processes

// designed for 4 processes only.

int main (int argc, char* argv[])
{
  int my_rank,np;
  double localarray[2];
  double globalarray[8];
  int root = 0;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  if (my_rank == root)
    {
      globalarray[0] = 1.0;
      globalarray[1] = 2.0;
      globalarray[2] = 3.0;
      globalarray[3] = 4.0;
      globalarray[4] = 5.0;
      globalarray[5] = 6.0;
      globalarray[6] = 7.0;
      globalarray[7] = 8.0;
    }
  

  MPI_Scatter(globalarray,8,MPI_DOUBLE,
             localarray,2,MPI_DOUBLE,
	     root,MPI_COMM_WORLD);

  printf("Process %d: a = %lf %lf\n",my_rank,localarray[0],localarray[1]);


  
  MPI_Finalize();
  return(0);
}

