#include <stdio.h>
#include <mpi.h>

// MPI_Ssend
// deadlocking example.  Always deadlocks, because Ssend is synchronous (nonlocal)

int main (int argc, char* argv[])
{
  int my_rank,np;
  int a = 10, b = -1;
  MPI_Status status;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  if (my_rank == 0)
    {
      MPI_Ssend(&a,1,MPI_INT,1,0,MPI_COMM_WORLD);
      MPI_Recv(&b,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
    }
  else
    {
      MPI_Ssend(&a,1,MPI_INT,0,0,MPI_COMM_WORLD);
      MPI_Recv(&b,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
    }

  printf("Process %d: a = %d, b = %d\n",my_rank, a, b);


  
  MPI_Finalize();
}

