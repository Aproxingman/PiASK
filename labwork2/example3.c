#include<omp.h>
#include<stdio.h>
main()
{
int p=0;
int s=0;
 omp_set_num_threads(4);
 #pragma omp parallel private(p) shared(s)
 {
 p+=1;
 s+=1;
 printf("omp: private p=%d, shared s=%d\n",p,s);
 }
 printf("private p=%d, shared s=%d\n",p,s);
}

