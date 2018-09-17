#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
  int my_rank,np;
  int a = 10, b = -1;
  int flag = 0;
  int elapsed = 0; // elapsed time in milliseconds
  int count;
  unsigned int delay = 10;
  MPI_Status status;
  MPI_Request req,req_r;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

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

  // right now, we have four outstanding requests.  Let's spin in a loop, testing
  // for the completion of the receive on process 0, to see just how long it takes
  // for the message on process 0 to be received.
  if (my_rank == 0)
  {
     while (!flag)
     {
        MPI_Test(&req_r,&flag,&status);        
        usleep(delay);
        elapsed += delay;
        printf("Message has not been received yet; elapsed time = %d ms\n",elapsed);
     }
    MPI_Get_count(&status,MPI_INT,&count);
    printf("Message has arrived! Elapsed time = %d ms.  Message length is %d items.\n",elapsed,count);
  } 
  else
  {
    MPI_Wait(&req_r,&status);
  }

  // clean up the send
  MPI_Wait(&req,&status);
  printf("Process %d: a = %d, b = %d\n",my_rank, a, b);


  
  MPI_Finalize();
}

