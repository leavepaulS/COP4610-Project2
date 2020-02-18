#include<stdio.h>
#include<unistd.h>
int main()
{

 const char mesg[] = "Hello";
 // first system call
 syscall(4,STDOUT_FILENO, mesg,sizeof(mesg)-1);
 printf("Hello World\n");
 int i =0;

 return 0;
}
