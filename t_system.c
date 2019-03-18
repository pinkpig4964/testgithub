#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_CMD_LEN 200

int main(int argc, char *argv[])
{
		//system 함수에서 실행할 명령을 저장하기 위한 문자열 배열
		char str[MAX_CMD_LEN];
		//system함수가 실행 후 종료시 실행결과값을 저장할 변수
		int status;
		//while(1)과 동일
		for(;;){
				printf("command: ");
				fflush(stdout);

				//fgets함수 입력 문자열 정상이 아닌  경우
				if(fgets(str,MAX_CMD_LEN, stdin)==NULL)
					break;
				//정상인 경우
				status = system(str);
				//실행 후 상태 찍어보는 것
				printf("system() returned : status = 0x%04x (%d %d)\n",
						(unsigned int) status,status >> 8, status & 0xff);
				
				if(status == -1)
				{
					printf("system\n");
				}
				else{
						if(WIFEXITED(status)&&WEXITSTATUS(status) ==127)
								printf("probably could not invoke shel\n");
				}
		}
				exit(0);
}
