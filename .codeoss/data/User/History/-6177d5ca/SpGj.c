#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "wgrep: searchterm [file ...]\n");
        return 1;;
    }

    char *search = argv[1];

    if (argc == 2) {
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        while ((nread = getline(&line, &len, stdin)) != -1) {
            if (strstr(line, search) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
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