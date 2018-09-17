#include <stdio.h>
#include <mpi.h>

// MPI_Isend()
// MPI_Irecv()
// nonblocking send, nonblocking receive

int main (int argc, char* argv[])
{
  int my_rank,np;
  int a = 10, b = -1;
  MPI_Status status;
  MPI_Request req,req_r;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  char procname[1024];
  int charcnt;
  MPI_Get_processor_name(procname,&charcnt);

  printf("Process %d is running on machine %s\n",my_rank,procname);

  if (my_rank == 0)
    {
      a = 5;
      MPI_Isend(&a,1,MPI_INT,1,0,MPI_COMM_WORLD,&req);
      MPI_Irecv(&b,1,MPI_INT,1,0,MPI_COMM_WORLD,&req_r);
    }
  else
    {
      MPI_Isend(&a,1,MPI_INT,0,0,MPI_COMM_WORLD,&req);
      MPI_Irecv(&b,1,MPI_INT,0,0,MPI_COMM_WORLD,&req_r);
    }

   // do some other work not dependent on b.
   // and, make sure not to touch a.

  printf("Process %d: a = %d, b = %d\n",my_rank, a, b);


  
  MPI_Finalize();
}


