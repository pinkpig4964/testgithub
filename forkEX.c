#include <stdio.h>//printf()
#include <unistd.h>//fork()
#include <sys/types.h>//pid_t
int main(void)
{
	pid_t pid;

	int x=0;

	pid=fork();
	x=1;
	printf("\n");
	if(pid==0){
		
	printf("pid=%ld  I am process %ld and getppid= %ld\n",(long)pid,(long)getpid(),(long)getppid());
	}
	else

	printf("pid=%ld  I am process %ld\n ",(long)pid,(long)getpid());
	//printf("pid=%ld  I am process %ld and my x is %d\n",(long)pid,(long)getpid(),x);
	return 0;
}
