#include<omp.h>
#include<stdio.h>
#include"my_timers.h"
#define NBR_OF_ELEMENTS 10
main()
{
long i=0;
int f[NBR_OF_ELEMENTS];
 omp_set_num_threads(4);
 start_time();
 f[0] = 0;
 f[1] = 1;
 #pragma omp parallel for
 for( i=2; i<NBR_OF_ELEMENTS; i++)
 {
         f[i] = f[i-1] + f[i-2];
         printf("%d : %d ",i, f[i]);
 }
 stop_time();
 print_time("Elapsed:");


}
