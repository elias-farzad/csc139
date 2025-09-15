// Elias Farzad
// This reverses the lines in a file given an input and outputting it to an output file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void die_malloc(void) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    // this is for too many inputs
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    // make sure input and output are different names
    if (argc == 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        return 1;
    }

    // input
    FILE *in = stdin;
    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    }

    // output
    FILE *out = stdout;
    if (argc == 3) {
        out = fopen(argv[2], "w");
        if (out == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            if (in != stdin) fclose(in);
            return 1;
        }
    }

    // read all lines, store pointers, then print in reverse
    char **lines = NULL;
    size_t count = 0, cap = 0;

    char *line = NULL;
    size_t buf_len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &buf_len, in)) != -1) {
        // store this line pointer; have getline allocate a new one next time
        if (count == cap) {
            size_t new_cap = (cap == 0) ? 16 : cap * 2;
            char **tmp = (char **)realloc(lines, new_cap * sizeof(*lines));
            if (!tmp) {
                free(line);
                // free already-stored lines
                for (size_t i = 0; i < count; i++) free(lines[i]);
                free(lines);
                die_malloc();
            }
            lines = tmp;
            cap = new_cap;
        }
        lines[count++] = line;
        line = NULL;      // force getline to allocate a fresh buffer next read
        buf_len = 0;
    }
    free(line); // safe if NULL

    // Output in reverse order
    for (ssize_t i = (ssize_t)count - 1; i >= 0; i--) {
        if (fprintf(out, "%s", lines[i]) < 0) {
            // If desired, could handle write errors; spec doesn't require
        }
        free(lines[i]);
    }
    free(lines);

    // Close files if they were opened
    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);

    return 0;
}
