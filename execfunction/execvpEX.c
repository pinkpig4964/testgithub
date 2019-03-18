#include <stdio.h>
#include <unistd.h>
/*
  int execv(const char *path, char *const argv[]);

  path에 지정한 경로명에 있는 파일을 실행하며 argv를 인자로 전달한다. argv는 포인터 배열이다. 이 배열의 마지막에는 NULL 문자열을 저장해야 한다.



  출처: https://unabated.tistory.com/entry/exec-함수군 [랄라라]
*/
int main()
{
	char *argv[] = {"ls" , "-al" , "/tmp", NULL};
	execlp("ls", "ls", "-al", "/tmp", NULL);
	execvp("ls" ,argv);

	printf("이 메세지가 보이면 지정된 프로그램이 없거나 어떤 문제로 실행되지 못한 것입니다.\n");
}
