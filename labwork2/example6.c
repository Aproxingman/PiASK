#include<omp.h>
#include<stdio.h>
#include"my_timers.h"
#define NBR_OF_ELEMENTS 1000000
#define NBR_OF_ELEMENTS_PER_THREAD (NBR_OF_ELEMENTS/4)
main()
{
long i=0;
double a[NBR_OF_ELEMENTS];
double sum=0.0;
double check=0.0;
double sum1, sum2, sum3, sum4;
 omp_set_num_threads(4);
start_time();

for (i = 0 ; i < NBR_OF_ELEMENTS; i++){
        a[i] = 1.0/rand();
        check+=a[i];

}
 #pragma omp parallel sections private(i)
 {

#pragma omp section
for( i=0; i<NBR_OF_ELEMENTS_PER_THREAD; i++){
        sum1+=a[i];

 }


 #pragma omp section

 for( i=NBR_OF_ELEMENTS_PER_THREAD ; i<(2 * NBR_OF_ELEMENTS_PER_THREAD) ; i++){
	sum2 += a[i];
}
 
 #pragma omp section

 for (i = (2 * NBR_OF_ELEMENTS_PER_THREAD ); i< (3 * NBR_OF_ELEMENTS_PER_THREAD) ; i++){
	sum3 += a[i]; 
}

 #pragma omp section

 for (i = (3 * NBR_OF_ELEMENTS_PER_THREAD ); i < NBR_OF_ELEMENTS; i++){
	sum4 += a[i];
 
}
} 
sum = sum1 + sum2 + sum3 + sum4; 
 stop_time();
 printf("Sum=%e, Check=%e\n", sum, check);
 print_time("Elapsed:");
}

