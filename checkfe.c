#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define buf_size 30
int main(void)
{
	char buf[buf_size];
	int i=0;
	int cnt =0;
	printf("please enter your strings. >>");
	fgets(buf,sizeof(buf),stdin);
	buf[strlen(buf)-1]='\0';

	for(i=0;i<buf_size/2;i++){
		
		if(buf[i]==buf[buf_size-1-i]){
				cnt++;
				printf("yes %d\n",cnt);
		}
		else if(buf[i]!=buf[buf_size-1-i]){
				printf("it is not palindrome\n");
				return 0;
		}
	}
	printf("it is palindrome\n");

	return 0;
}
