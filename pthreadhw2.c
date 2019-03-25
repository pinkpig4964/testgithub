#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define DATASIZE sizeof(int)*4

void* t_function(void *data)
{
		long i;
		long long result = 0;
		pthread_t t_id;
		int argData;
		argData = *((int *)data);
		t_id=pthread_self();
		sleep(argData);
		printf("getpid=%d, tid=%lu, argData:%d\n", getpid(), t_id, argData);
		for (i = 1; i < 200001; i++)
		{
				result +=i;
		}
		printf("result = %lld\n ", result);
		printf("\n");
		sleep(1);

		return (void*)(argData*argData);

}

int main(void)
{
		pthread_t p_thread;
		int ret;
		int a=1;
		int status;

		struct timeval startTime, endTime;
		double diffTime;
		gettimeofday(&startTime, NULL);
		if ((ret = pthread_create(&p_thread, NULL, t_function, (void*)&a)) < 0)
		{
				perror("Error:pthread_create1()");
				return -1;
		}
		pthread_join(p_thread, (void**)&status);
		gettimeofday(&endTime, NULL);
		diffTime = ( endTime.tv_sec - startTime.tv_sec ) + (( endTime.tv_usec - startTime.tv_usec ) / 1000000.0);
		printf("%f s\n", diffTime);
		printf("thread_join1:%d\n", status);
}
