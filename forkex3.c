#include <sys/types.h>
#include <unistd.h>

int glob=6;
char buf[] = "a write to stdout\n";

int main(void)
{
	int var;
	pid_t pid;
	var = 88;

	if(write(STDOUT_FILENO, buf, sizeof(buf)-1)!=sizeof(buf)-1)
			perror("write error");
	printf("before fork\n"); //we dont flush stdout

	if(pid = fork()==0){
		glob++;
		var++;}
	else
			sleep(2);
	printf("pid = %d, glob = %d, var  = %d\n",getpid(),glob,var);
	exit(0);
}
