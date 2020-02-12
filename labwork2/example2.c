#include<omp.h>
#include<stdio.h>
int main()
{
 omp_set_num_threads(4);
 #pragma omp parallel
 {
 printf("My ID is %d\n",omp_get_thread_num());
 }//end parallel
}
