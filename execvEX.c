#include <stdio.h>
#include <unistd.h>
/*
execv 함수는 execv("path", 인자);로 구성된 함수로 위와 같이
5번줄 :path에서 실행할 인자와 execv 함수의 1번째 매개변수인 인자를 실행할 path로 구성된다.
*/
void main()
{
		char *argv[] = {"ls", "-a", 0};
		//"파일명", "인자", 인자 끝 0(iNULL) 표시 배열
		execv("/bin/ls",argv);
		//execv("경로", 인자 배열)
}
