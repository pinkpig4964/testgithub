static void sig_handler(int signum)
static void sig_killhandler(int signum)
{
	printf("I got signal : signum=%d\n",signum);
	printf("sig_killhandler : signum=%d\n",signum);
	exit(0);
}

static void sig_inthandler(int signum)
{
	printf("sig_inthandler : signum=%d\n",signum);
	exit(0);
}

int main(void)
{
	int status;
	pid_t pid;
	pid=fork();
	//자식 프로세스일 경우
	if(pid==-1)
	{
		printf("Error:fork pid=-1");
		return -1;
	}
	else if(pid==0)
	{
		//핸들러에 등록이 불가능한 시그널
		signal(SIGKILL,sig_handler);
		if(signal(SIGKILL,sig_killhandler)==SIG_ERR)
			printf("\ncan't catch SIGKILL\n");

		if(signal(SIGINT,sig_inthandler)==SIG_ERR)
			printf("\ncan't catch SIGINT\n");

		while(1)
		{
			printf("Hello world\n");
			sleep(1);
		}
	}
	else
	{
		sleep(10);
		kill(pid,SIGKILL);
	}
	wait(&status);
	pr_exit(status);
	return 0;
}
