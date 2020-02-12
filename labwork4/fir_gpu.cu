/*** fir.gpu.cu**/

#include <stdio.h>
/** Tool function*/

void random_ints(int* a, int N){
int i;
 for(i = 0; i < N; ++i)
 a[i] = (int)(rand() / (RAND_MAX + 1.0) * 10.0);
}

/** CUDA parameters */

#define BLOCK_SIZE 512

// Define fir coefficients in the texture memory
#define COEF_NBR 5

__constant__ int C[]={1, -2, 4, -2, 1};
int h_C[]={1, -2, 4, -2, 1}; //host fir coefficients
/* * FIR kernel */

__global__ void fir(int *D, int *O) {
int index = threadIdx.x + blockIdx.x * blockDim.x;
int i;
 O[index] = 0;
 for(i=0; i<COEF_NBR; i++)
 O[index] += C[i] * D[index + i];
}

/** FIR kernel that uses shared memory */

__global__ void fir_fast(int *D, int *O) {
int index = threadIdx.x + blockIdx.x * blockDim.x;
__shared__ int tmpD[BLOCK_SIZE + COEF_NBR-1]; // reserve with overlapped data
__shared__ int tmpC[COEF_NBR];
__shared__ int tmpO[BLOCK_SIZE];
int i; //my loop iterator

 // Copy block of input data to shared memory
 tmpD[threadIdx.x] = D[index];
 // Copy overlapped input data
 if( threadIdx.x < COEF_NBR-1 )
 tmpD[blockDim.x + threadIdx.x] = D[(blockIdx.x+1) * blockDim.x + threadIdx.x];
 // Copy fir coefficients
 if( threadIdx.x < COEF_NBR)
 tmpC[threadIdx.x] = C[threadIdx.x];

 __syncthreads();

 tmpO[threadIdx.x] = 0;
 for(i=0; i<COEF_NBR; i++)
 tmpO[threadIdx.x] += tmpC[i] * tmpD[threadIdx.x + i];
 __syncthreads();
  O[index] = tmpO[threadIdx.x];
}

/** host program */

int main(void) {
int *h_D, *h_O; // host copies of D, O
int *d_D, *d_O; // device copies of D, O
int nBlk = 512;
int nThx = BLOCK_SIZE;
int N = nBlk * nThx;
int sizeD = (N + COEF_NBR) * sizeof(int);
int sizeO = N * sizeof(int);
int i, j; //my loop iterators
int result;
 // Alloc space for device copies of D, O
 cudaMalloc((void **)&d_D, sizeD);
 cudaMalloc((void **)&d_O, sizeO);

 // Alloc space for host copies of D, O and setup input values
 h_D = (int *)malloc(sizeD); random_ints(h_D, N+COEF_NBR);
 h_O = (int *)malloc(sizeO);

 // Copy input data to device
 cudaMemcpy(d_D, h_D, sizeD, cudaMemcpyHostToDevice);

cudaEvent_t start, stop;
float time;
cudaEventCreate(&start);
cudaEventCreate(&stop);
cudaEventRecord(start, 0);

 // Launch add() kernel on GPU with N threads
 fir<<<nBlk,nThx>>>(d_D, d_O);


cudaEventRecord(stop, 0);
cudaEventSynchronize(stop);
cudaEventElapsedTime(&time, start, stop);
printf("GPU time is %f ms\n", time);

 // Copy result back to host
 cudaMemcpy(h_O, d_O, sizeO, cudaMemcpyDeviceToHost);
 //Checkup
 for(i=0; i<N; i++){
 result=0;
 for(j=0; j<COEF_NBR; j++)
 result += h_C[j] * h_D[i + j];
 if( result != h_O[i] ){
 printf("Error at %d. %d != %d\n", i, h_O[i], result);
 goto cleanup;
 }
 }
 printf("Success\n");
cleanup:
 // Cleanup
 free(h_D); free(h_O);
 cudaFree(d_D); cudaFree(d_O);
 return 0;
}



