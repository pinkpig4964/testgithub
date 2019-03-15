/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2018.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/
/*
int execl(const char *path, const char *arg0, ..., const char *argn, (char*) 0);
 path에 지정한 경로명의 파일을 실행하여 arg0~argn을 인자로 전달한다. 관례적으로 arg0에는 실행 파일명을 지정한다. execl 함수의 마지막 인자로는 인자의 끝을 의미하는 NULL포인터((char*)0)를 지정해야한다. path에 지정하는 경로명은 절대 경로나 상대 경로 모두 사용할 수 있다.
 */
/* Listing 27-5 */

#include <stdlib.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    printf("Initial value of USER: %s\n", getenv("USER"));
    if (putenv("USER=britta") != 0)
        errExit("putenv");

    execl("/usr/bin/printenv", "printenv", "USER", "SHELL", (char *) NULL);
    errExit("execl");           /* If we get here, something went wrong */
}
