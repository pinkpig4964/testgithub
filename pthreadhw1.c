#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define DATASIZE sizeof(int)*4

long long result = 0;
void* t_function1(void *data)
{
		int i;
		pthread_t t_id;
		int argData;
		int just=0;
		argData = *((int *)data);
		if(argData==2)
				just =100000;
		t_id=pthread_self();
		sleep(argData);
		printf("getpid=%d, tid=%lu, argData:%d\n", getpid(), t_id, argData);
		for (i = just+1; i <just+ 100001; i++)
		{
				result +=i;
		}
		printf("result = %lld\n ", result);
		printf("\n");

		return (void*)(result);

}
/*
void* t_function2(void *data)
{
		int i;
		pthread_t t_id;
		int argData;
		argData = *((int *)data);
		t_id=pthread_self();
		sleep(argData);
		printf("getpid=%d, tid=%lu, argData:%d\n", getpid(), t_id, argData);
		for (i = 1000001; i < 2000001; i++)
		{
				result +=i;
		}
		printf("result = %lld\n ", result);
		printf("\n");
		sleep(5);

		return (void*)(argData*argData);

}*/
int main(void)
{
		pthread_t p_thread[2];
		int ret;
		int a=1;
		int b=2;
		long long status;

		struct timeval startTime, endTime;
		double diffTime;
		gettimeofday(&startTime, NULL);
		if ((ret = pthread_create(&p_thread[0], NULL, t_function1, (void*)&a)) < 0)
		{
				perror("Error:pthread_create1()");
				return -1;
		}

		if ((ret = pthread_create(&p_thread[1], NULL, t_function1, (void*)&b)) < 0)
		{
				perror("Error:pthread_create2()");
				return -2;
		}
		pthread_join(p_thread[0], (void**)&status);

		printf("thread_join1:%lld\n", status);
		pthread_join(p_thread[1], (void**)&status);

		printf("thread_join2:%lld\n", status);
		gettimeofday(&endTime, NULL);
		diffTime = ( endTime.tv_sec - startTime.tv_sec ) + (( endTime.tv_usec - startTime.tv_usec ) / 1000000);
		printf("%f s\n", diffTime);
}
