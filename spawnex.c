#include <stdio.h>
#include <sys/wait.h>
#include <spawn.h>
#include <sys/types.h>
int my_posix_spawn(const char *path, char *const argv[])
{
	pid_t pid;
	int ret = posix_spawn(&pid, path, NULL, NULL, argv, NULL);

	int status;
	waitpid(pid, &status, 0);

	return ret;
}
int main()
{
	char path[] = "/bin/ls";
	char *argv_ls[] = {"ls", "-al", NULL};

	my_posix_spawn(path, argv_ls);

	return 0;
}
