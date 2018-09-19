#include <stdio.h>
#include <mpi.h>

// MPI_Reduce()
// example of data reduction

int main (int argc, char* argv[])
{
  int my_rank,np;
  double a[2];
  double a_global[2];
  int root = 0;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  a[0] = 1.0;
  a[1] = (double)my_rank/(double)np;

  root = np-1;

  MPI_Reduce(a,a_global,2,MPI_DOUBLE,MPI_SUM,root,MPI_COMM_WORLD);

  printf("Process %d: a_global= %lf %lf\n",my_rank,a_global[0],a_global[1]);
  
  MPI_Finalize();
  return(0);
}

