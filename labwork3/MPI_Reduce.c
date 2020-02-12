#include <mpi.h>
#include <stdio.h>
main(int argc, char** argv){
int i;
int myrank;
int size;
int root=1;
int sum;
 MPI_Init(&argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 MPI_Reduce(&myrank, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
 printf("Process %d sum: %d\n", myrank, sum);
 MPI_Finalize();
}

