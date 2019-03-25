#if defined(__GNU_LIBRARY__)&& !defined(_SEM_SEMUN_UNDEFINED)
/*union semyn is defined by including <sys/sem.h>*/

#else
/*according to X/OPEN we have to define it ourselves*/
	union semun{
			int val;
			struct semid_ds *buf;
			unsigned short int *array;
			struct seminfo *__buf;
	};
#endif
