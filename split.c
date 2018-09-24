#include <stdio.h>
#include <mpi.h>

// example of splitting a communicator with
// MPI_Comm_split
// 
//All processes which pass in the same value for color are assigned to the same communicator. 
//If the color is MPI_UNDEFINED, that process won’t be included in any of the new communicators. 
//The third argument, key, determines the ordering (rank) within each new communicator. 
//The process which passes in the smallest value for key will be rank 0, the next smallest will be rank 1, and so on. 
//If there is a tie, the process that had the lower rank in the original communicator will be first. 
//The final argument, newcomm is how MPI returns the new communicator back to the user.
//

// run with 4 processes

int main (int argc, char* argv[])
{
  int my_rank,np,my_new_rank,new_np;
  int a = 10, b = -1;
  int color,key;
  MPI_Status status;
  MPI_Comm new_comm;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  // split the communicator; odd processes go in one
  // communicator, while even processes go in another
  // communicator.  Furthermore, reverse the ordering
  // of the processes in the new subcommunicator
  color = my_rank % 2; 
  key = np - my_rank;
  //key = 0; 
  MPI_Comm_split(MPI_COMM_WORLD,color,key,&new_comm);

  MPI_Comm_rank(new_comm,&my_new_rank);
  MPI_Comm_size(new_comm,&new_np);

  printf("Process %d (in COMM_WORLD) is process %d (in split communicator)\n",
		  my_rank,my_new_rank);
  printf("Process %d (in COMM_WORLD): COMM_WORLD has %d processes\n",
		 my_rank,np);
  printf("Process %d (in COMM_WORLD): split communicator has %d processes\n",
		  my_rank,new_np);

  MPI_Comm_free(&new_comm);

  
  MPI_Finalize();

  return(0);
}

