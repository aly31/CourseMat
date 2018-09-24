#include <stdio.h>
#include <mpi.h>

#define RED "\033[01;31m"
#define RESET "\033[22;0m"


// example of using MPI_Pack and MPI_Unpack 

// process zero sends a count and status flag, followed by "count" doubles, to process one.
int main (int argc, char* argv[])
{
  int i,my_rank,np;
  MPI_Status status;
  int position;
  int size;
  char *pbuffer = NULL;
  int bufsz = 0;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  if (my_rank == 0)
    {
      // set the sample data that we want to pack and send
      int count = 5;
      double ddata[5];
      int stat_flag = 4542;
      for (i = 0; i < 5; i++) ddata[i] = (double)i;

      // figure out the size of the buffer we will need
      MPI_Pack_size(1,MPI_INT,MPI_COMM_WORLD,&size);   bufsz += size;
      MPI_Pack_size(1,MPI_INT,MPI_COMM_WORLD,&size);   bufsz += size;
      MPI_Pack_size(count,MPI_DOUBLE,MPI_COMM_WORLD,&size);   bufsz += size;
      pbuffer = (char*)malloc(bufsz);
      printf("Process 0 (sender): buffer size to pack into is %d bytes\n",bufsz);

      // pack the message
      position = 0;
      MPI_Pack(&count,1,MPI_INT,pbuffer,bufsz,&position,MPI_COMM_WORLD); 
      MPI_Pack(&stat_flag,1,MPI_INT,pbuffer,bufsz,&position,MPI_COMM_WORLD); 
      MPI_Pack(ddata,count,MPI_DOUBLE,pbuffer,bufsz,&position,MPI_COMM_WORLD); 
  
      // send
      MPI_Send(pbuffer,bufsz,MPI_PACKED,1,0,MPI_COMM_WORLD);
     
    }
  else
    {
      int count;
      int stat_flag;
      double *ddata = NULL;
      position = 0;

      // probe to get the size of the incoming message 
      MPI_Probe(0,0,MPI_COMM_WORLD,&status); 
      MPI_Get_count(&status,MPI_PACKED,&bufsz);
      printf(RED"Process 1 (receiver): incoming message size is  %d bytes\n",bufsz);

      // allocate memory for the packed data.
      pbuffer = (char*)malloc(bufsz);

      // receive the message
      MPI_Recv(pbuffer,bufsz,MPI_PACKED,0,0,MPI_COMM_WORLD,&status);

      // unpack data
      MPI_Unpack(pbuffer,bufsz,&position,&count,    1,MPI_INT,MPI_COMM_WORLD);
      MPI_Unpack(pbuffer,bufsz,&position,&stat_flag,1,MPI_INT,MPI_COMM_WORLD);

      ddata = (double*)malloc(sizeof(double)*count); 
      MPI_Unpack(pbuffer,bufsz,&position,ddata,count,MPI_DOUBLE,MPI_COMM_WORLD);

      printf("Process 1: received %d data items with a status flag of %d.\n",count,stat_flag); 
      for (i = 0; i < count; i++) printf("Process 1: ddata[%d] = %lf\n",i,ddata[i]);
      printf(RESET);
      free(ddata);
    }


  free(pbuffer);
  MPI_Finalize();

  return(0);
}

