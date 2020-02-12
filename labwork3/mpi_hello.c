#include <mpi.h>
#include <stdio.h>
main(int argc, char** argv){
	 int np, rank;
	 MPI_Init( &argc, &argv);
	 //Get total number of MPI processes
	 MPI_Comm_size( MPI_COMM_WORLD, &np );
	 //Get my unique id (rank)
 	 MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   	 printf("Hello. I am %d out of %d ...\n", rank, np);
     	 MPI_Finalize();
      }
