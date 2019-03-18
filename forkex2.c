#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int global = 10;
int main(void){
	int i = 20;
	pid_t pid;
	int status;

	pid = fork();

	if(pid == 0){
			global = global+10;
			i=i+10;
	}
	else
			global = global+100; i = i+100;
	wait(&status);
	printf("global = %d, i = %d\n",global,i);
}
