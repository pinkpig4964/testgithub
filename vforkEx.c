#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int glob=0;
int main(void)
{
	int var;
	pid_t pid;

	var = 88;
	printf("before vfork\n");

	if((pid=vfork())<0)
			puts("vfork error");
	else if(pid == 0){
			glob++;
			var++;
			printf("Child pid = %d, glob=%d, var = %d\n",getpid(),glob, var);
			exit(0);
	}
	
			printf("pid = %d, glob=%d, var = %d\n",getpid(),glob, var);
			exit(0);
}
