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

    // same file check (when 2 args)
    if (argc == 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        return 1;
    }

    // pick input
    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else {
        in = stdin; // no input file -> read from stdin
    }

    // pick output
    if (argc == 3) {
        out = fopen(argv[2], "w");
        if (out == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            if (in != stdin) fclose(in);
            return 1;
        }
    } else {
        out = stdout; // default to screen
    }

    // ok now read all lines and store them (we don't know how many)
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

    // getline gave up; free the scratch buffer if it exists
    free(line);

    // now print in reverse order (simple countdown)
    // careful with size_t being unsigned: count down like this
    size_t i = n;
    while (i > 0) {
        i--;
        // print exactly the line (includes its \n if present)
        if (fprintf(out, "%s", lines[i]) < 0) {
            // spec doesn't say what to do on write errors, so ignoring
        }
        free(lines[i]); // free as we go
    }
    free(lines);

    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);

    return 0;
}
