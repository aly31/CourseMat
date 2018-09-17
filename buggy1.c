#include <stdio.h>
#include <mpi.h>

#define RED "\033[01;31m"
#define RESET "\033[22;0m"


// MPI_Send()
// deadlocking example, with increasing message size. 
// demonstrates the transition between eager standard mode
// sends and rendezvous standard mode sends
//
#define MAX_MESSAGE_LEN 16383

int main (int argc, char* argv[])
{
  int my_rank,np,i;
  int message_len;
  int *a=NULL, *b=NULL;
  MPI_Status status;

  MPI_Init(&argc,&argv);
  printf("MPI_Init has been called.\n");
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  for (message_len = 2; message_len <= MAX_MESSAGE_LEN; message_len *= 2)
   {
      a = (int*)malloc(message_len*sizeof(int));
      b = (int*)malloc(message_len*sizeof(int));
      for (i = 0; i < message_len; i++) a[i] = i; 

      printf(RED"My message consists of %d bytes (not taking the envelope into account)\n"RESET,message_len*sizeof(int));

      if (my_rank == 0)
       {
         MPI_Send(a,message_len,MPI_INT,1,0,MPI_COMM_WORLD);
         MPI_Recv(b,message_len,MPI_INT,1,0,MPI_COMM_WORLD,&status);
       }
       else
       {
          MPI_Send(a,message_len,MPI_INT,0,0,MPI_COMM_WORLD);
          MPI_Recv(b,message_len,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       }

       printf(RED"Process %d: a[%d] = %d, b[%d] = %d\n"RESET,my_rank, 
           message_len-1, a[message_len-1], message_len-1, b[message_len-1]);

       sleep(1); //pause for dramatic effect ;)

       free(a);
       free(b);
   } 


  MPI_Finalize();
  return(0);
}

