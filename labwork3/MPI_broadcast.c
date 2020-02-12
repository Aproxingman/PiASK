#include <mpi.h>
#include <stdio.h>
main(int argc, char** argv){
	int i;
	int myrank;
	int size;
	int root=2;
	int value;
 	MPI_Init(&argc, &argv);
 	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
 	value=(myrank+1)*(myrank+1);
 	printf("Own process %d value: %d\n", myrank, value);
 	MPI_Bcast(&value, 1, MPI_INT, root, MPI_COMM_WORLD);
 	printf("Root value from %d: %d\n", myrank, value);
 	MPI_Finalize();
}
