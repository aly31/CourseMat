#include <stdio.h>
#include <mpi.h>


#define RED "\033[01;31m"
#define RESET "\033[22;0m"

// example of using MPI_Pack and MPI_Unpack 

// rank zero sends a count and status flag, followed by "count" doubles, to process one.
int main (int argc, char* argv[])
{
  int i,my_rank,np;
  MPI_Status status;
  int position;
  char pbuffer[1000];  // arbitrarily use a 1000 byte buffer.
                       // (this will be corrected in the next example)

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  if (my_rank == 0)
    {
      int count = 5;
      double ddata[5];
      int stat_flag = 4542;
      for (i = 0; i < 5; i++) ddata[i] = (double)i;
      position = 0;
      MPI_Pack(&count,1,MPI_INT,pbuffer,1000,&position,MPI_COMM_WORLD); 
      MPI_Pack(&stat_flag,1,MPI_INT,pbuffer,1000,&position,MPI_COMM_WORLD); 
      MPI_Pack(ddata,count,MPI_DOUBLE,pbuffer,1000,&position,MPI_COMM_WORLD); 
      MPI_Send(pbuffer,1000,MPI_PACKED,1,0,MPI_COMM_WORLD);
    }
  else
    {
      int count;
      int stat_flag;
      double *ddata = NULL;
      position = 0;
      MPI_Recv(pbuffer,1000,MPI_PACKED,0,0,MPI_COMM_WORLD,&status);
      MPI_Unpack(pbuffer,1000,&position,&count,    1,MPI_INT,MPI_COMM_WORLD);
      MPI_Unpack(pbuffer,1000,&position,&stat_flag,1,MPI_INT,MPI_COMM_WORLD);

      ddata = (double*)malloc(sizeof(double)*count); 
      MPI_Unpack(pbuffer,1000,&position,ddata,count,MPI_DOUBLE,MPI_COMM_WORLD);

      printf(RED"Process 1: received %d data items with a status flag of %d.\n",count,stat_flag); 
      for (i = 0; i < count; i++) printf("Process 1: ddata[%d] = %lf\n",i,ddata[i]);
      printf(RESET);
      free(ddata);
    }


  MPI_Finalize();

  return(0);
}

