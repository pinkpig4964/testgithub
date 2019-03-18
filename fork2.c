#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	char *message;
	int n;

	printf("fork program starting\n");
	pid = fork();
	int status;
	switch(pid)
	{
		case -1:
				perror("fork failed\n");
				exit(1);
		case 0:
				message = "This is the child";
				n=5;
				break;
		default:
				message = "This is the parent";
				n=3;
				break;
	}
/*	for( ; n>0 ; n--)
	{
			puts(message);
			sleep(1);
	}*/

	wait(&status);
	for( ; n>0 ; n--){
			printf("%s\n",message);
			sleep(1);
	}
//	wait(&status);
	if(pid>0)
	{
		printf("Child Proc State : Zombie, about %d sec\n", 20);
		sleep(20);
		wait(NULL);
	}
	
	exit(0);
}
