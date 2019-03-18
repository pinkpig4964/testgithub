#include <stdio.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
	struct stat sb;

	if(argc!=2)
	{
		printf("Usage: %s <pathname>\n",argv[0]);
	}
	if(stat(argv[]& sb)==-1)
	{
		fprintf(stderr,"Error : stat()\n");
		return -1;
	}

	printf("^============================================================\n");
	printf("FILE type:");
	switch(sb.st_mode & S_IFMT)
	{
		case S_IFBLX : printf("block device\n"); break;
		case S_IFCHR : printf("char device\n"); break;
		case S_IFDIR : printf("directory\n"); break;
		case S_IFIFO : printf("FIFO\n"); break;
		case S_IFLINK : printf("symlink\n"); break;
		case S_IFREG : printf("regular file\n"); break;
		case S_IFSOCK : printf("socket\n"); break;
		default : printf("unknown\n");break;
	}
	printf("I-node numver : %ld\n",(long) sb.st_ino);
	printf("mode : %ld\n",(long) sb.st_mode);	
	printf("LINK count  : %ld\n",(long) sb.st_nLink);
	printf("Owneship  UID : %ld , GID : %ld bytes  \n",(long) sb.st_uid,sb.st_gid);
	printf("Preferred I/O block size : %ld bytes\n",(long) sb.st_blksize);
}

	printf("File size : %ldbytes \n",(long) sb.st_size);
	printf("Blocks allocated  : %ld\n",(long) sb.st_blocks);
	printf("Last status change  : %s\n",(long) sb.st_ctime);
	printf("Last file access : %s\n",(long) sb.st_atime);
	printf("Last file modification  : %s\n",(long) sb.st_mtime);

	return 0;
}
