#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//IPC & semaphore
#include <sys/sem.h>
#include <sys/ipc.h>
/*
 struct sembuf
 {
	short sem_num;//세마포어 번호
	short sem_op;//세마포어 증감값
	short sem_flg;//옵션
 }
IPC_NOWAIT :호출 즉시 실행하지 못했을 경우 기다리지 않고 실패로 바로 복귀합니다.

SEM_UNDO : 프로세스가 종료되면 시스템에서 세마포어 설정을 원래 상태로 되돌립니다. (보통 이 옵션을 사용)

semop(semid->getid를 통해 받음, 세마포어 스트럭쳐 주소, 세마포어 개수 대첵로 1)
 */
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
}arg;

int cnt = 0;
static int semid;
void p()
{
	struct sembuf pbuf;
	pbuf.sme_num=0;
	pbuf.sem_op = -1;
	pbuf.sem_flg = SEM_UNDO;
	if(semop(semid, &pbuf, 1)==-1)
		perror("p:semop()");
}

void v()
{
	struct sembuf vbuf;
	pbuf.sme_num=0;
	pbuf.sem_op = 1;
	pbuf.sem_flg = SEM_UNDO;
	if(semop(semid, &pbuf, 1)==-1)
		perror("v:semop()");
}

int main(int argc, char *argv[])
{
	//step1 semaphoreget()
	if((semid=semget(IPC_PRIVATE, 1, IPC_CREAT|0665))==-1)
	{
		perror("Error: semget()");
		return -1;
	}

	arg.val = 1;
	//step 2 semaphore ctl :SETVALUE
	if(semctl(semid, 0, SETVAL,arg)==-1)
	{
			perror("Error semctl() : SETVAL");
			return -1;
	}

	//test code
	while(1)
	{
		if(cnt<9){
			cnt++;
			v();
			printf("increase :%d\n",cnt);
			usleep(100);
		}
		else{
				p();
				cnt--;
				printf("decrease: %d\n",cnt);
				break;
		}
		//step3 semctl : IPC_RMID
		if(semctl(semid, 0,IPC_RMID, arg)==-1)
		{
			perror("semctl() :IPC_RMID");
		}
		return 0;
	}

}
