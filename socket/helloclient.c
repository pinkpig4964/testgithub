#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MSG_SIZE 100
void errorhandling(char *message)
{
		fputs(message, stderr);
		fputs("\n",stderr);
		exit(1);
}

int main(int argc, char* argv[])
{
	int sock; //fd
	struct sockaddr_in serv_addr;
	char message[MSG_SIZE];
	int str_len;

	if(argc!=3)
	{
			//helloClient [SERVER_IPADDR] [SERVER_PORTNUM]
			printf("Usage: %s IP PORT\n",argv[0]);
			exit(1);
	}
	//STEP 1 : socket을 생성한다
	//PF_INET은 IPv4을 뜻함
	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock == -1)
	{
			error_handling("socket error");
	}

	//STEP 2 :접속할 서버의 ip주소, 포트번호, 프로토콜을 정의
	memset(&serv_addr , 0, sizeof(serv_addr));
	serv_addr.sin_family =AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	//STEP 3 : 접속 요청-접속할 때의 주소 포트
	if(connet(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
	{
		errorhandling("connect error");
	}
	//STEP 4 : 데이터 수신
	str_len = read(sock, message, sizeof(message)-1);
	
	if(str_len == -1)
	{
		errorhandling("read error");

	}
	printf("message from server : %s\n" , message);
	//STEP 5 :소켓 종료
	close(sock);
	return 0;

}
