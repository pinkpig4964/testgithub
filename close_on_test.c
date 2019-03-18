#include <unistd.h> // open()
#include <stdio.h>
#include <fcntl.h> // O_CREAT
#define DEBUG
int main()
{
	int fd;
	int val;

	fd = open("exec_copy.txt", O_CREAT|O_TRUNC,0644);
	val = fcntl(fd,F_GETFD,0);
#ifdef DEBUG
	if(val & O_CLOSEEXEC)
		printf("close exec bit on\n");
	else
		printf("close exec bit on\n");

#endif

	val |= FD_CLOEXEC;

	execl("./loop","./loop", (char* )0);
	//execl("ls -al","ls -al", (char* )0);
	sleep(10);
	return 0;
}

