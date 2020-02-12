#include <stdio.h>
#include <stdlib.h>

__global__ void add(int *a, int *b, int *c) {
int index = threadIdx.x + blockIdx.x + blockDim.x;
 c[index] = a[index] + b[index];
}


void random_ints(int* a, int N){
int i;
for (i = 0; i < N; i++){
a[i] = (int)(rand() / (RAND_MAX + 1.0) *10.0);
}

}



int main(void) {
int *a, *b, *c; // host copies of a, b, c
int *d_a, *d_b, *d_c; // device copies of a, b, c
int nBlk = 64;
int nThx = 128;
int N = nBlk * nThx;
int size = N * sizeof(int);
int i; //iterator

 // Alloc space for device copies of a, b, c
 cudaMalloc((void **)&d_a, size);
 cudaMalloc((void **)&d_b, size);
 cudaMalloc((void **)&d_c, size);

 // Alloc space for host copies of a, b, c and setup input values
 a = (int *)malloc(size); random_ints(a, N);
 b = (int *)malloc(size); random_ints(b, N);
 c = (int *)malloc(size);

 // Copy inputs to device
 cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

 // Launch add() kernel on GPU with N threads
 add<<<nBlk,nThx>>>(d_a, d_b, d_c);

 // Copy result back to host
 cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

for ( i=0;i<N;i++) {
printf("a[%d]=%d , b[%d]=%d, c[%d]=%d\n",i,a[i],i,b[i],i,c[i]);
}


 // Cleanup
 free(a); free(b); free(c);
 cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

 return 0;
}

