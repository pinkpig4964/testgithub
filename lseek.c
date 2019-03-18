#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd;
	
	fd= open("./testlseek.txt",O_RDWR);
	//write(fd, "hello", 5);
	
	int buf_size = sizeof(testlseek.txt);
	if(buf_size <=0)
			printf("buf_size error\n");
	//lseek(fd,10,SEEK_CUR);
	//write(fd,"world",5);

	//lseek(fd,892,SEEK_SET);
	//write(fd,"bye",3);
	close(fd);
	return 0;
}
