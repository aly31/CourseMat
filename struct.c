
#include <stdio.h>
#include <mpi.h>

// example of using MPI derived datatypes
// MPI_Type_struct

struct stuff {
  double d;
  char c[2];
  int i;
};

int main (int argc, char* argv[])
{
  int my_rank,np;
  int i,sz,lb,ub,ex;
  struct stuff s;
  MPI_Status status;
  MPI_Datatype newtype;
  MPI_Aint displ[3];
  MPI_Aint addresses[3];
  MPI_Aint base_address;
  int block_lengths[3];
  MPI_Datatype typelist[3];

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  //
  // build our datatype
  //
  typelist[0] = MPI_DOUBLE;
  typelist[1] = MPI_CHAR;
  typelist[2] = MPI_INT;
  
  block_lengths[0] = 1;
  block_lengths[1] = 2;
  block_lengths[2] = 1;

  MPI_Address(&s,&base_address);
  MPI_Address(&s.d,&addresses[0]);
  MPI_Address(&s.c,&addresses[1]);
  MPI_Address(&s.i,&addresses[2]);
  displ[0] = addresses[0] - base_address;
  displ[1] = addresses[1] - base_address;
  displ[2] = addresses[2] - base_address;
#if 0
  displ[0] = &s.d - &s.d;
  displ[1] = &s.c - &s.d;
  displ[2] = &s.i - &s.d;
#endif

  printf("Displacements = %d %d %d\n",displ[0],displ[1],displ[2]);
			    
// note that the first argument basically tells the size of blocklenghts and displs and typelist
// size of all the arrays  

  MPI_Type_struct(3,block_lengths,displ,typelist,&newtype);

  MPI_Type_commit(&newtype);


  //
  // send a message to test our datatype
  //
  if (my_rank == 0)
    {
      MPI_Type_size(newtype,&sz);
      MPI_Type_get_extent(newtype,&lb,&ex);
      ub = lb + ex;
      printf("sizeof s = %d\n",sizeof(s));
      printf("size = %d\n",sz);
      printf("ub   = %d\n",ub);
      printf("lb   = %d\n",lb);
      printf("ex   = %d\n",ex);

      // fill in data to send
      s.i = 10;
      s.d = 40.0;
      s.c[0] = 'a';
      s.c[1] = 'c';
      MPI_Send(&s,1,newtype,1,0,MPI_COMM_WORLD);
    }
  else
    {
      // receive data
      MPI_Recv(&s,1,newtype,0,0,MPI_COMM_WORLD,&status);

      // print the results
      printf("Process 1: s = %lf %d %c %c\n",s.d,s.i,s.c[0],s.c[1]);

    }

  MPI_Type_free(&newtype); 

  MPI_Finalize();

  return(0);
}

