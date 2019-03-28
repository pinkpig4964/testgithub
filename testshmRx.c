//지금 하는 거
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
		//void *shmaddr;
		int i;
		myData person[10];
		myData *shmaddr=NULL;
		//struct myData person;
		int personNum=0;
		int running =1;
		int sum=0;
		int ave=0;
		char* testaddr;
		// step0. ftok()

		// step1. shmget
		shmid = shmget((key_t)1234, sizeof(int)*SHMSIZE, 0666 | IPC_CREAT);
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

		//	shmaddr = (int*)shared_Mem;

		shmaddr = (myData*)shared_Mem;
	/*	testaddr = (char*)shared_Mem;
		printf("shmaddr:%p\n",shmaddr);
		printf("personaddr:%p\n",person);

		*(testaddr+8)='a';
		*(testaddr+9)='b';
		*(testaddr+10)=0;

		printf("testdata:%s\n",testaddr);*/

	//	memcpy(person,shared_Mem,sizeof(myData)*10);
		//memcpy(&person[0],&shmaddr[0],sizeof(myData)*10);
/*
		testaddr = (char*)person;
		printf("testaddr:%p\n",testaddr);
		printf("persondata:%s\n",testaddr+8);
		printf("Name:%s", person[0].name);
*/
		
		while(running){
			//person[personNum]=*(shmaddr+personNum);
				//memcpy(&person[personNum],shmaddr+(sizeof(struct myData))*personNum, sizeof(person));
				if(shmaddr[personNum].msgType ==2){
						printf("msgType = %ld\n",shmaddr[personNum].msgType);
						running = 0;
				}
				else{
						printf("Receive Data Person[%d]\n", personNum);
						printf("Name:%s", shmaddr[personNum].name);
						sum = shmaddr[personNum].eng_scor + shmaddr[personNum].kor_scor + shmaddr[personNum].mat_scor;
						ave = sum / 3;
						printf("총점:%d\n", sum);
						printf("average:%d\n", ave);

				}
				personNum++;
		}
		//sleep(4);

//		memcpy(person,shared_Mem,sizeof(myData)*10);
		//memcpy(person,shmaddr,sizeof(myData)*10);
		// step4. shmdt
		if (shmdt(shared_Mem) == -1)
		{
				fprintf(stderr, "shmdt failed\n");
				exit(EXIT_FAILURE);
		}

		// step5. shmctl : IPC_RMID
		if (shmctl(shmid, IPC_RMID, 0) == -1)
		{
				fprintf(stderr, "shmctl (IPC_RMID) failed\n");
				exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
}
