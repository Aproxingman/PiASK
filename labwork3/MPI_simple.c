#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
int p, src, dest, rank;
int tag = 1;
char mes[50];
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &p);
 if ( rank != 0 ) {
 sprintf(mes, "Hello, this is process %d", rank);
 dest = 0;
 MPI_Send(mes, strlen(mes) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
 }
 if (rank==0) {
 MPI_Recv(mes, 50, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD,&status);
 printf("%s\n", mes);
 }
 MPI_Finalize();
 return 0;
}

