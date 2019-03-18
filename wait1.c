#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void pr_exit(int status)
{
	//정상 종료인 경우
	if(WIFEXITED(status))
			printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	//시그널에 의해서 종료인 경우
	else if(WIFSIGNALED(status))
			printf("abnormal terminaionm signal number = %d%s\n",WTERMSIG(status),WCOREDUMP(status) ? "(core file generated)" : "");
	//시그널에 의해 STOP된 경우
	else if(WIFSTOPPED(status))
			printf("child stopped, signal number = %d\n",WSTOPSIG(status));
}
int main()
{
	pid_t pid;
	char *message;
	int n;
	int exit_code;
	int status;
	printf("fork program starting\n");
	pid = fork();
	switch(pid)
	{
			case -1: perror("fork failed");
					 exit(1);
			case 0: message = "This is the child";
					n=5;
					exit_code = 37;
					break;
			default:
					message = "This is the paraent";
					n = 3;
					exit_code = 0;
					break;
	}
	for(; n>0 ; n--)
	{
		puts(message);
		sleep(1);
	}
	if(pid!=0)
	{
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);
		printf("child has finished: PID = %d\n",child_pid);
		/*
		if(WIFEXITED(stat_val))
						printf("child exited with code %d\n",WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");*/
		pr_exit(status);
	}
	exit(exit_code);

	

}
