#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define DOMAIN_SIZE	400


void get_full_domain(double* full_domain, int* full_domain_length)
{
	int iter = 0;
        //full_domain = (double*)malloc(sizeof(double)*DOMAIN_SIZE);
    	for(iter = 0; iter < DOMAIN_SIZE; iter++)
        		{
  		full_domain[iter] = 4.00 + 0.01*iter;
   	//printf("my_domain: %f \n;",full_domain[iter]);
      					}
      //full_domain = my_domain;
      *full_domain_length = DOMAIN_SIZE;	
       //printf("Full domain length: %d\n\n",*full_domain_length);
        }
       


void compute(double* local_domain, int local_domain_length, double* local_min)
{
	int i = 0;
	double min = 0, value = 0;
	min = pow((local_domain[0]-5),3) -pow((local_domain[0]-4),2) + 1;

	for (i = 1; i < local_domain_length; i++)
	{
		value = pow((local_domain[i] - 5),3) - pow((local_domain[i]-4),2) + 1;
		if ( value < min )
		{
			min = value;
			
		}
		
	}
	*local_min = min;
}

main(int argc, char** argv){
int i;
int myrank;
int size;
int root;
int full_domain_length;
int sub_domain_length;
double global_min;
double local_min;
root = 0;
double *full_domain;
double *sub_domain;
 MPI_Init( &argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 

if (myrank == root) {
 full_domain = (double*) malloc(sizeof(double)*DOMAIN_SIZE);
 get_full_domain(full_domain, &full_domain_length);
 }


 MPI_Bcast(&full_domain_length, 1, MPI_INT, root, MPI_COMM_WORLD);


sub_domain_length = full_domain_length / size;

 sub_domain = (double *) malloc(sub_domain_length * sizeof(double));
 MPI_Scatter(full_domain, sub_domain_length, MPI_DOUBLE,
 sub_domain, sub_domain_length, MPI_DOUBLE,
 root, MPI_COMM_WORLD);

 compute(sub_domain, sub_domain_length, &local_min);
 MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE,
 MPI_MIN, root, MPI_COMM_WORLD);
	printf("min: %lf \n", global_min);


 MPI_Gather(sub_domain, sub_domain_length, MPI_DOUBLE,
 full_domain, sub_domain_length, MPI_DOUBLE,
 root, MPI_COMM_WORLD);
 MPI_Finalize();

}
