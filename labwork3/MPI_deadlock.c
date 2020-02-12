#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
	int p, src, dest, rank;
	int tag = 1;
	char mes[]="Message ...\n";
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	printf("Process %d is running\n", rank);
	if(rank==0) dest=1; else dest=0;
	MPI_Ssend(mes, strlen(mes) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	MPI_Recv(mes, 50, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
 	printf(mes);
 	MPI_Finalize();
 	return 0;
}
