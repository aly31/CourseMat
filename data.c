#include <stdio.h>
#include <mpi.h>

// MPI_Send()
// non deadlocking (with MPICH), but not safe!
// datatype mismatch example

int main (int argc, char* argv[])
{
  int my_rank,np;
  int errcode;
  float a = 10.0;
  double  b = -1.0;
  MPI_Status status;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  if (my_rank == 0)
    {
      errcode = MPI_Recv(&b,1,MPI_DOUBLE,1,0,MPI_COMM_WORLD,&status);
      MPI_Send(&a,1,MPI_FLOAT,1,0,MPI_COMM_WORLD);
      printf("RECV on process %d: error flag = %d %d\n",0,status.MPI_ERROR,errcode);
      if (status.MPI_ERROR == MPI_ERR_TYPE) printf("Mismatch in datatype detected.\n");
    }
  else
    {
      MPI_Send(&a,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);
      errcode = MPI_Recv(&b,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);
      printf("RECV on process %d: error flag = %d %d\n",1,status.MPI_ERROR,errcode);
      if (status.MPI_ERROR == MPI_ERR_TYPE) printf("Mismatch in datatype detected.\n");
    }

  printf("Process %d: a = %lf, b = %f\n",my_rank, a, b);


  
  MPI_Finalize();
}

