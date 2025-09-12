#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "wcat: cannot open file\n");
            return 1;
        }

        char buf[4096];
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            fputs(buf, stdout);
        }

        fclose(fp);
    }

    return 0;
}