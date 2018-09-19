#include <stdio.h>
#include <mpi.h>

// MPI_Gather()
// example of gathering data
// gather data related to the process ranks to the root process


int main (int argc, char* argv[])
{
  double *array = NULL;
  int my_rank,np;
  double a;
  int root = 0;
  int i;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  a = (double)my_rank/(double)np;

  if (my_rank == root) 
	    {
      array = (double*)malloc(np*sizeof(double));
       }

  MPI_Gather(&a,1,MPI_DOUBLE,
             array,1,MPI_DOUBLE,
	     root,MPI_COMM_WORLD);

   
  if (my_rank == root)
  { 
  for (i = 0; i < np; i++)
  {
	  printf("Process %d: array[%d] = %.15E\n",my_rank,i,array[i]);
  } 
  }


  free(array);
 
  MPI_Finalize();
  return(0);
}

