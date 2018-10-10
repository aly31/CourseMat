#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define MAX_PROCS 1024

int main (int argc, char* argv[])
{
  int my_rank,np,i;
  int n_global;
  int root = 0;
  int counts[MAX_PROCS],displs[MAX_PROCS];
  MPI_File fha,fhb;
  double *v1 = NULL;
  double *v2 = NULL;
  double dotp=0.0,dotp_global=0.0;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  MPI_File_open(MPI_COMM_WORLD,"a.c.dat",MPI_MODE_RDONLY,MPI_INFO_NULL,&fha);
  MPI_File_open(MPI_COMM_WORLD,"b.c.dat",MPI_MODE_RDONLY,MPI_INFO_NULL,&fhb);
  MPI_File_read(fha,&n_global,1,MPI_INT,MPI_STATUS_IGNORE);
  // on all process, compute how many entries should go to each process
  for (i = 0; i < np; i++) counts[i] = n_global/np;
  for (i = 0; i < n_global % np; i++) counts[i]++;
  displs[0] = 0;
  for (i = 1; i < np; i++) displs[i] = displs[i-1]+counts[i-1];

  printf("my_rank =%d, nglobal = %d, displ=%d\n",my_rank,n_global,displs[my_rank]);

  // allocate memory for vectors
  v1 = (double*)malloc(counts[my_rank]*sizeof(double));
  v2 = (double*)malloc(counts[my_rank]*sizeof(double));

  // read data 
  MPI_File_seek(fha,sizeof(int) + sizeof(double)*displs[my_rank],MPI_SEEK_SET);
  MPI_File_seek(fhb,sizeof(int) + sizeof(double)*displs[my_rank],MPI_SEEK_SET);
  MPI_File_read(fha,v1,counts[my_rank],MPI_DOUBLE,MPI_STATUS_IGNORE);
  MPI_File_read(fhb,v2,counts[my_rank],MPI_DOUBLE,MPI_STATUS_IGNORE);

  // close file
  MPI_File_close(&fha);
  MPI_File_close(&fhb);

  for (i = 0; i < counts[my_rank]; i++)
  {
     dotp += v1[i]*v2[i];
  }

  free(v1);
  free(v2);
// reduce
  MPI_Reduce(&dotp,&dotp_global,1,MPI_DOUBLE,MPI_SUM,root,MPI_COMM_WORLD);
  
  if (my_rank == root)
  {
     printf("Dot product is %.15E\n",dotp_global);
  }  
  

  MPI_Finalize();

  return(0);
}

