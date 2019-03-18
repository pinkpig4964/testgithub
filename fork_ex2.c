#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
void my_exec(const char* path, char *const argv[])
{
	int ret;
	pid_t pid;

	pid = fork();
	if(pid == -1){
			perror("fork");
			exit(EXIT_FAILURE);
	}
	if(pid ==0)
	{
			ret = exec(path, argv);

			if(ret == -1)
			{
					perror("execv");
					exit(EXIT_FAILURE);
			}
	}
	wait(NULL);
}
int main(void)
{
	char path[] = "/bin/ls";
	char *argv_ls[] = {"ls","-al",NULL};
	my_execv(path, argv_ls);

	return 0;
}
