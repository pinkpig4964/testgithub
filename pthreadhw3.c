#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define DATASIZE sizeof(int)*4
typedef struct
{
		int start;
		int end;
}Arg;
//int input;
void* t_function(void *data)
{
		long long i;
		long long result = 0;
		pthread_t t_id;
		Arg  argData;
		long long start;
		
		argData = *((Arg*)data);
		t_id=pthread_self();
		//sleep(argData);
		for (i = argData.start; i <argData.end+1; i++)
		{
				result +=i;
		}
		printf("result = %lld\n ", result);
		printf("\n");

		return (void*)(result);
		//return (void*)(argData*argData);

}

int main(int argc,char* argv[])
{
		pthread_t p_thread;
		int ret;
		int a=1;
		Arg *arg;
		arg = (Arg*)malloc(sizeof(Arg));

		long long status;
		if(argv[1]==NULL || argv[2] == NULL){
			printf("input error: argv\n");
			return -1;
		}
		arg->start= atoll(argv[1]);
		
		arg->end= atoll(argv[2]);
		struct timeval startTime, endTime;
		double diffTime;
		//input  =atoi(argv[1]);
		gettimeofday(&startTime, NULL);
		if ((ret = pthread_create(&p_thread, NULL, t_function, (void*)arg)) <     0)

		{
				perror("Error:pthread_create1()");
				return -1;
		}
		pthread_join(p_thread, (void**)&status);
		gettimeofday(&endTime, NULL);
		diffTime = ( endTime.tv_sec - startTime.tv_sec ) + (( endTime.tv_usec - startTime.tv_usec ) / 1000000.0);
		printf("%f s\n", diffTime);
		printf("thread_join1:%lld\n", status);
		return 0;
}
