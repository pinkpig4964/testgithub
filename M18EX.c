#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

static void sig_quit(int);
static void sighandler(int signo);

void whatchild(int signo);
int main(void)
{
		sigset_t newmask, oldmask, pendmask;
		pid_t pid;

		pid = fork();
		if(pid == -1)
				printf("fork error\n");
		//child
		else if(pid == 0)
		{

				if(signal(SIGQUIT, sig_quit) ==SIG_ERR)
						perror("can't catch SIGQUIT\n");
				//Block SIGQUIT and save current signal mask
				sigemptyset(&newmask);
				sigaddset(&newmask, SIGUSR1);
				sigaddset(&newmask, SIGUSR2);
				if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0)
				{
						perror("SIG Block error\n");
				}
				sleep(5);

				if(sigpending(&pendmask)<0)
						perror("sigpending error\n");
				//if(sigismember(&pendmask, SIGQUIT))
				//	printf("\nSIGQUIT pending\n");
				//Reset signal mask which unblocks SIGQUIT
				if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0)
						perror("SIG_SETMASK error\n");
				//printf("SIGQUIT unblocked\n");

				sleep(5);
				if(sigismember(&newmask, SIGUSR1))
						printf("Hello\n");
				if(sigismember(&newmask, SIGUSR2))
						printf("world\n");
				sig_quit(SIGUSR1);
				sig_quit(SIGUSR2);
		}
		//parent
		else
		{
				signal(SIGUSR1, sighandler);
				sleep(1);
				signal(SIGUSR2, sighandler);
				int stat_val;
				pid_t child_pid;
				child_pid=wait(&stat_val);
				if(WIFEXITED(stat_val)){
						printf("parent will be exited\n");
						exit(0);
				}
		}
		/*
		   if(signal(SIGQUIT, sig_quit) ==SIG_ERR)
		   perror("can't catch SIGQUIT\n");
		//Block SIGQUIT and save current signal mask
		sigemptyset(&newmask);
		sigaddset(&newmask, SIGUSR1);
		sigaddset(&newmask, SIGUSR2);
		if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0)
		{
		perror("SIG Block error\n");
		}
		sleep(5);

		if(sigpending(&pendmask)<0)
		perror("sigpending error\n");
		//if(sigismember(&pendmask, SIGQUIT))
		//	printf("\nSIGQUIT pending\n");
		//Reset signal mask which unblocks SIGQUIT
		if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0)
		perror("SIG_SETMASK error\n");
		//printf("SIGQUIT unblocked\n");

		sleep(5);
		 */
		exit(0);

}	
static void sig_quit(int signo)
{
		printf("caught SIGQUIT\n");
		if(signal(SIGQUIT, SIG_DFL) == SIG_ERR)
				perror("can't reset SIGQUIT\n");
}
static void sighandler(int signo)
{
		signal(SIGINT, signo);
		whatchild(signo);
}
void whatchild(int signo)
{
		if(signo == SIGUSR1){
				// sigusr1일 때 해야하는 일
				printf("Hello sigusr1\n");
		}
		else if(signo == SIGUSR2)
		{
				//sigusr2일 때 해야하는 일
				printf("world sigusr2\n");
			
		}
		else
				printf("fail\n");
}
