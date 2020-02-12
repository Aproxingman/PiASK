/**
* File: hello_gpu.cu
**/
/* Kernel – does nothing*/

#include <stdio.h>

__global__ void mykernel(void) {
}

int main(void) {
 mykernel<<<1,1>>>(); /* Launch mykernel on GPU */
 printf("Hello GPU!\n");
 return 0;
}
