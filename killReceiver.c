#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int sig)
{
		printf("Kill Test :I got signal %d\n", sig);
		(void)signal(SIGINT, SIG_DFL);
}
int main(void)
{
		signal(SIGINT, sigHandler);
		while(1)
		{
				printf("hello world\b");
				sleep(1);
		}
}
