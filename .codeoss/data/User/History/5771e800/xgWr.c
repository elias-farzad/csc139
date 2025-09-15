#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        return 0;
    }

    FILE *fp = fopen("main.c", "r");
    if (fp == NULL) {
        printf("cannot open file\n");
        exit(1);
    }
}