#include<unistd.h>
#include<stdio.h>
int main()
{
 printf("Start. My ID is %d\n", getpid());
 fork();
 fork();
 printf("Message from process %d\n", getpid());

 }

