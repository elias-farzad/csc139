#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "wunzip: cannot open file\n");
            return 1;
        }

        int count;
        int ch;
        while (fread(&count, sizeof(int), 1, fp) == 1) {
            ch = fgetc(fp);
            if (ch == EOF) {
                fclose(fp);
                return 0;
            }

            const size_t BUFSZ = 8192;
            char buf[8192];
            for (size_t k = 0; k < BUFSZ; k++) buf[k] = (char)ch;

            while (count > 0) {
                size_t chunk = count < (int)BUFSZ ? (size_t)count : BUFSZ;
                fwrite(buf, 1, chunk, stdout);
                count -= (int)chunk;
            }
        }

        fclose(fp);
    }

    return 0;
}