#include <stdio.h>
#include <mpi.h>

#define RED "\033[01;31m"
#define RESET "\033[22;0m"

// example of using MPI derived datatypes
// MPI_Type_vector

int main (int argc, char* argv[])
{
  int my_rank,np;
  int a[10],i,sz,lb=0,ub=0,ex=0;
  MPI_Status status;
  MPI_Datatype vtype;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

   printf("my_rank %d\n", my_rank);
  // create a vector; five entries, one integer a piece,
  // with a stride of 2
  //case 1//
    MPI_Type_vector(5,1,2,MPI_INT,&vtype);

  //case 2//
  //  MPI_Type_vector(5,1,1,MPI_INT,&vtype);

  // create a vector; five entries, two integer a piece,
  // with a stride of 2

  //case 3//
//  MPI_Type_vector(5,2,2,MPI_INT,&vtype);


  MPI_Type_commit(&vtype);

  MPI_Type_size(vtype,&sz);
/*
  MPI_Type_get_extent(vtype,&lb,&ex);
  ub = lb + ex;
  printf("size = %d\n",sz);
  printf("ub   = %d\n",ub);
  printf("lb   = %d\n",lb);
  printf("ex   = %d\n",ex);
*/


  if (my_rank == 0)
    {
      for (i = 0; i < 10; i++) a[i] = i+1;

      for (i = 0; i < 10; i++) 
         {
          printf("Process %d: a[%d] = %d\n",my_rank,i,a[i]);
          }

      MPI_Send(a,1,vtype,1,0,MPI_COMM_WORLD);
    }
  else if(my_rank==1)
    {
      for (i = 0; i < 10; i++) a[i] = -1;

      MPI_Recv(a,1,vtype,0,0,MPI_COMM_WORLD,&status);

      for (i = 0; i < 10; i++) printf(RED"Process %d: a[%d] = %d\n",my_rank,i,a[i]);
      printf(RESET);
    }

  MPI_Type_free(&vtype); 

  MPI_Finalize();

  return(0);
}

