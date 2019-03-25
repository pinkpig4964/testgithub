#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


// For IPC function
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct myData
{
	long int msgType; //default
	char name[20];
	int kor_scor;
	int eng_scor;
	int mat_scor;
};

int main(void)
{
	int running = 1;
	struct myData person[10];
	int msgid;
	int personNum = 0;
	//char buffer[BUFSIZ];

	//step0. ftok();

	//step1. msgget 
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1)
	{
		fprintf(stderr, "Error:msgget failed : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while (running)
	{
		printf("0~9의 Number: \n");
		scanf("%d", &personNum);
			while (getchar() != '\n');
		printf("Name:");
		fgets(person[personNum].name, sizeof(person[personNum].name), stdin);

			while (getchar() != '\n');
		if (!strncmp(person[personNum].name, "end", 3))
		{
			person[personNum].msgType = 2;
			running = 0;
		}
		else
		{
			printf("국어 점수:");
			scanf("%d", &person[personNum].kor_scor);
			while (getchar() != '\n');
			printf("영어 점수:");
			scanf("%d", &person[personNum].eng_scor);
			while (getchar() != '\n');
			printf("수학 점수:");
			scanf("%d", &person[personNum].mat_scor);
			while (getchar() != '\n');
			person[personNum].msgType = 1;

			//입력 버퍼 비우기
			while (getchar() != '\n');
		}


		//step2. msgsnd
		if (msgsnd(msgid, &person[personNum], sizeof(person) - sizeof(long), 0) == -1)
		{
			//메시지가 정상적으로 전달되지 않은 경우
			fprintf(stderr, "Error:msgsnd failed : %d\n", errno);
			exit(EXIT_FAILURE);
		}

	}
	exit(EXIT_SUCCESS);
}

