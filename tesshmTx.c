//Tx
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//For IPC 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE	100 //int * 100
typedef struct
{
	long int msgType;
	char name[20];
	int kor_scor;
	int eng_scor;
	int mat_scor;
}myData;
int main(void)
{
	void *shared_Mem = (void*)0;
	int shmid;
	myData *shmaddr;
	int i;
	myData person[10];
	int personNum=0;
	int running =1;
	int test;
	// step0. ftok()

	// step1. shmget
	shmid = shmget((key_t)1234, sizeof(myData)*10, 0666 | IPC_CREAT);
	if (shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// step2. shmat
	shared_Mem = shmat(shmid, (void*)0, 0);
	if (shared_Mem == (void*)-1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Memory attached at %p\n", (int*)shared_Mem);
	shmaddr = (myData*)shared_Mem;
	//memcpy(&shmaddr[0], &person[0], sizeof(myData)*10);
	//memcpy(shmaddr, person, sizeof(myData)*10);
	//memcpy(shared_Mem, person, sizeof(myData)*10);
	//*shmaddr = person;
	// step3. memory access
	/*
	   for (i = 0; i < SHMSIZE; i++)
	   {
	 *(shmaddr + i) = i + 1;
	 printf("shmaddr:%X, data:%d\n", shmaddr + i, *(shmaddr + i));
	 }*/

	while(running){
		/*틀렸으면 여기를 지워*/
		//printf("0~9의 Number: \n");
		//scanf("%d", &personNum);
		while (getchar() != '\n');
		printf("Name:");
		fgets(shmaddr[personNum].name, sizeof(shmaddr[personNum].name), stdin);

		//printf("person name: %s\n",person[personNum].name);
	//	while (getchar() != '\n');
		if (!strncmp(shmaddr[personNum].name, "end", 3))
		{
			shmaddr[personNum].msgType = 2;
			running = 0;
		}

		else
		{
			printf("국어 점수:");
			scanf("%d",&shmaddr[personNum].kor_scor);
			while (getchar() != '\n');
			//while (getchar() != '\n');
			//printf("korean sc = %d\n",person[personNum].kor_scor); 
			printf("영어 점수:");
			scanf("%d", &shmaddr[personNum].eng_scor);
			while (getchar() != '\n');
			printf("수학 점수:");
			scanf("%d", &shmaddr[personNum].mat_scor);
			while (getchar() != '\n');
			shmaddr[personNum].msgType = 1;
			if(shmaddr[personNum].msgType==1)
					test=personNum;
			//입력 버퍼 비우기
	//		while (getchar() != '\n');
		}
	//printf("%s %d %d\n",person[personNum].name, person[personNum].kor_scor, person[personNum].eng_scor);
		personNum++;
	}
	//sleep(4);

	
	//shared_Mem=(void*)person;
	// step4. shmdt
	if (shmdt(shared_Mem) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	/*
	  //원래 여기 없애야해
	// step5. shmctl : IPC_RMID
	if (shmctl(shmid, IPC_RMID, 0) == -1)
	{
	fprintf(stderr, "shmctl (IPC_RMID) failed\n");
	exit(EXIT_FAILURE);
	}
	 
	*/
	exit(EXIT_SUCCESS);
}


