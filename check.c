#include <stdio.h>
#include <string.h>
#define buf_size 20

int is_palindrome(char *s)
{
	int len = strlen(s);

	int left = 0;
	int right = len-1;

	while((right-left)>1){
			if(s[right]!=s[left]){
					printf("it is not palindrome\n");
					return 0;
			}

			left +=1;
			right -=1;
	}
	return 1;
}

int main(){
	char buf[buf_size];

	printf("put your string to check > ");
	fgets(buf,sizeof(buf),stdin);
	buf[strlen(buf)-1]='\0';

	if(is_palindrome(buf)==1){
		printf("yes it is palindrome\n");
	}
	else
			printf("no...\n");
	return 0;
}
