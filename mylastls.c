#include <sys/types.h>
#include <grp.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pwd.h>
#include <sys/types.h>
void access_perm(char *perm, mode_t mode)
{
	int i;
	char permchar[] = "rwx";
	memset(perm, '-', 10);

	perm[10] = '\0';
					
	if (S_ISDIR(mode)) perm[0] = 'd';
	
	else if (S_ISCHR(mode)) perm[0] = 'c';
	
	else if (S_ISBLK(mode)) perm[0] = 'b';
	
	else if (S_ISFIFO(mode)) perm[0] = 'p';
	
	else if (S_ISLNK(mode)) perm[0] = 'l';

	for (i = 0; i < 9; i++)	
	{
	
			if ((mode << i) & 0x100)
			
					perm[i+1] = permchar[i%3];
					
	}
	
	if (mode & S_ISUID) perm[3] = 's';
	
	if (mode & S_ISGID) perm[6] = 's';
	
	if (mode & S_ISVTX) perm[9] = 't';
}

int main(int argc, char *argv[])
{
	DIR *dp;
	
	struct stat statbuf;
	uid_t user_id;
	struct passwd *user_pw;
	char forus[10];
	char forgr[10];
	struct group *group_pw;

	struct dirent *dent;

	
	char perm[11];
	
	char pathname[80];
	struct tm *tm;
	char timestr[100];
	
	if (argc < 2) 
	
			exit(1);

	stat(argv[1], &statbuf);
	
	if (!S_ISDIR(statbuf.st_mode)) 
	{
	
			fprintf(stderr, "%s is not directory\n",argv[1]);
			
			exit(1);
																				}

			
	if ((dp = opendir(argv[1])) == NULL) 
	{
	
			perror("Error:");
			
			exit(1);
																					}
												
			
	printf("Lists of Directory(%s):\n", argv[1]);

	
	while((dent = readdir(dp)) != NULL) 
	
	{		
			user_id = getuid();
			user_pw = getpwuid(user_id);
			group_pw = getgrgid(statbuf.st_gid);
			sprintf(forus, "%s",user_pw->pw_name);
			sprintf(forgr, "%s",group_pw->gr_name);
			sprintf(pathname, "%s/%s", argv[1], dent->d_name);
			
			lstat(pathname, &statbuf);
			
			access_perm(perm, statbuf.st_mode);
			tm =localtime(&statbuf.st_ctime);
			strftime(timestr,sizeof(timestr),"%m month %d %H:%M", tm);
			//printf("i did it\n");
			//printf("%s %8ld %s\n", perm,statbuf.st_size, dent->d_name);
			printf("%s %ld %s %s %8ld ", perm, statbuf.st_nlink, forus, forgr,statbuf.st_size)    ;
			printf("%s ",timestr);
			printf("%s\n ",dent->d_name);
	}

	
	closedir(dp);

	
	return 0;
}
