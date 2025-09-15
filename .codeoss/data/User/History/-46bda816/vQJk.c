// Elias Farzad
// This reverses the lines in a file given an input and outputting it to an output file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *in = NULL;
    FILE *out = NULL;

    // too many args error
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    // check if in and out are same file
    if (argc == 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        return 1;
    }

    // input
    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else {
        in = stdin;
    }

    // output
    if (argc == 3) {
        out = fopen(argv[2], "w");
        if (out == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            if (in != stdin) fclose(in);
            return 1;
        }
    } else {
        out = stdout; 
    }

    // read all lines and store them
    // plan: dynamic array of char* that we grow by doubling
    char **lines = NULL;
    size_t cap = 0;
    size_t n = 0;

    char *line = NULL;     // getline will malloc for us the first time
    size_t bufsize = 0;    // getline uses this to track capacity
    ssize_t got;

    // read loop
    while ((got = getline(&line, &bufsize, in)) != -1) {
        if (n == cap) {
            size_t newcap = (cap == 0) ? 8 : cap * 2;
            char **tmp = (char **)realloc(lines, newcap * sizeof(char *));
            if (tmp == NULL) {
                // free what we have so far then die
                free(line);
                for (size_t i = 0; i < n; i++) {
                    free(lines[i]);
                }
                free(lines);
                fprintf(stderr, "malloc failed\n");
                if (in != stdin) fclose(in);
                if (out != stdout) fclose(out);
                return 1;
            }
            lines = tmp;
            cap = newcap;
        }

        // store this line pointer, then force getline to allocate a fresh one next time
        lines[n++] = line;
        line = NULL;
        bufsize = 0;
    }

    // free scratch buffer
    free(line);

    // print in reverse order
    size_t i = n;
    while (i > 0) {
        i--;
        // print exactly the line (includes its \n if present)
        fprintf(out, "%s", lines[i]);
        free(lines[i]);
    }
    free(lines);

    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);

    return 0;
}
