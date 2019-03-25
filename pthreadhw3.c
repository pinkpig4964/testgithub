#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define DATASIZE sizeof(int)*4
//int input;
void* t_function(void *data)
{
		long long i;
		long long result = 0;
		pthread_t t_id;
		long long  argData;
		long long start;

		argData = *((long long *)data);
		t_id=pthread_self();
		//sleep(argData);
		printf("getpid=%d, tid=%lu, argData:%d\n", getpid(), t_id, argData);
		for (i = 1; i <argData+1; i++)
		{
				result +=i;
		}
		printf("result = %lld\n ", result);
		printf("\n");

		return (void*)(argData*argData);

}

int main(int argc,char* argv[])
{
		pthread_t p_thread;
		int ret;
		int a=1;
		int status;
		long long input = atoll(argv[1]);
		struct timeval startTime, endTime;
		double diffTime;
		//input  =atoi(argv[1]);
		gettimeofday(&startTime, NULL);
		if ((ret = pthread_create(&p_thread, NULL, t_function, (void*)&input)) <     0)

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
