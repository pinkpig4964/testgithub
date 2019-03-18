#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
static void sigHandler(int sig)

{
		static int count = 0;
		{
				count++;

				if(sig == SIGINT)
				{
					printf("Caught SIGINT(%d)\n",count);
					return;
				}
				else //if(sig == SIGQUIT)
				{
					
					printf("Caught SIGINT(%d)\n",count);
					return;
				}
		}
		printf("caught sigquit - that's all folks!\n");
		exit(0);
}
int main(int argc, char **argv)
{
	if(signal(SIGINT, sigHandler) == SIG_ERR)
			return 1;

	if(signal(SIGQUIT, sigHandler) == SIG_ERR)
			return 1;
	for(;;)
			pause();
	return 0;
}
