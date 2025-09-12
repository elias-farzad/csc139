#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "wzip: file1 [file2 ...]\n");
        return 1;
    }

    int count = 0;
    int c;
    int prev = EOF;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "wzip: cannot open file\n");
            return 1;
        }

        while ((c = fgetc(fp)) != EOF) {
            if (prev == EOF) {
                prev = c;
                count = 1;
            } else if (c == prev) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(prev, stdout);
                prev = c;
                count = 1;
            }
        }

        fclose(fp);
    }

    if (prev != EOF) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(prev, stdout);
    }

    return 0;
}