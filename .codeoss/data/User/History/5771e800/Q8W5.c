#include <stdio.h>
#include <stdlib.h>

int main(filename) {
    FILE *fp = fopen("main.c", "r");
    if (fp == NULL) {
        printf("cannot open file\n");
        exit(1);
    }
}