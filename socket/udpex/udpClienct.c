#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char* argv[])
{
	int sock; //fd
	int i;
	int result;
	struct calcul cal;
	struct sockaddr_in serv_addr,from_addr;
	int str_len;
	socklen_t adr_sz;

	if (argc != 3)
	{
		// ./calClient [SERVER_IPADDR] [PORT_NUM]
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}

	//STEP 1. socket을 생성한다. file의  open과 동일
	// PF_INET : IP v4
	// SOCK_DGRAM : UDP
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	//STEP 2. 접속할 서버의 IP주소, 포트번호, 프로토콜을 정의
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	while(1)
	{
		fputs("Insert message (q to quit) : ",stdout);
		fgets(message, sizeof(message), stdin);
		if(!strcmp(mesage,"q\n")||!strcmp(message, "Q\n"))
			break;
		sendto(sock, message, strlen(message),0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

		adr_sz = sizeof(from_addr);
		str_len = recvfrom(sock, message, MSG_SIZE,0, (struct sockaddr*)&from_addr,&adr_sz);

		message[str_len] = 0;
		printf("Message from server : %s",message);
		
	}

	close(sock);
	return 0;
}
		


