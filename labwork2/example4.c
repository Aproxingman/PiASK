#include<omp.h>
#include<stdio.h>
#include"my_timers.h"
#define NBR_OF_ELEMENTS 2000000
main()
{
long i=0;
float a[NBR_OF_ELEMENTS];
 omp_set_num_threads(3);
 start_time();
 #pragma omp parallel for
 for( i=0; i<NBR_OF_ELEMENTS; i++)
 a[i]=sqrt(i);
 stop_time();
 print_time("Elapsed:");
}

