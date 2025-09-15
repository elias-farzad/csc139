#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common.h"

int
main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address pointed to by p: %p\n", getpid(), p);
    printf("(pid:%d) addr stored in p: %llx\n", (int) getpid(), 
	   (unsigned long long) p);
    *p = atoi(argv[1]);       // assign value to addr stored in p
    while (1) {
	Spin(1);
	*p = *p + 1;
	printf("(pid:%d) value of p: %d\n", getpid(), *p);
    }

    return 0;
}

