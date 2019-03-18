#include <signal.h>
#include <stdio.h>
#include <unistd.h>
//SIGINT에 대응하는 핸들러
void sigHandler(int sig)
{		
		static int count = 0;
		printf("OUCH! i got signal %d\n",sig);
		if(count ==4)
			(void) signal(SIGINT,  SIG_DFN);
		count++;
}
int main()
{
	//SIGINT 신호가 수신되었을 떄.
	//sigHandler()함수가 호출되도록 등록
	signal(SIGINT, sigHandler);
	while(1)
	{
			printf("Hello wordl\n");
			sleep(1);
	}
}

