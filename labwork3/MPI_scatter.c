#include <mpi.h>
#include <stdio.h>
main(int argc, char** argv){
int i;
int myrank;
int size;
int root=1;
int value;
int buffer[]={0,1,2,3,4,5,6,7,8};
int sub_buf[]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
 MPI_Init(&argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 value=(myrank+1)*(myrank+1);
 MPI_Scatter(buffer, 8/size, MPI_INT,
 sub_buf, 8/size, MPI_INT,
 root, MPI_COMM_WORLD);
 printf("Process %d values: %d %d %d %d\n", myrank,
 sub_buf[0],sub_buf[1],sub_buf[2], sub_buf[3]);
 MPI_Finalize();
}
