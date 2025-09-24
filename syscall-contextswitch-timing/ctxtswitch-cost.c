// Elias Farzad
// This program estimates context switch cost by ping-ponging a byte between two processes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv) {
    // # of ping-pongs to run
    long long N = (argc > 1) ? atoll(argv[1]) : 1000000LL;

    int p12[2], p21[2];
    if (pipe(p12) || pipe(p21)) { perror("pipe"); return 1; }

    pid_t c = fork();
    if (c < 0) { perror("fork"); return 1; }

    // child process
    if (c == 0) {
        // close unused pipe ends
        close(p12[1]); // child doesn’t write to p12
        close(p21[0]); // child doesn’t read from p21

        char x;
        while (1) {
            // wait for a byte from parent
            ssize_t r = read(p12[0], &x, 1);
            if (r == 0) break;
            if (r < 0) { perror("child read"); break; }

            // Send byte back to parent
            if (write(p21[1], &x, 1) != 1) { perror("child write"); break; }
        }

        close(p12[0]);
        close(p21[1]);
        _exit(0);
    }

    // parent process
    // Close unused pipe ends
    close(p12[0]); // parent doesn’t read from p12
    close(p21[1]); // parent doesn’t write to p21

    char t = 'x', y;

    // record start time
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // do N ping-pongs
    for (long long i = 0; i < N; i++) {
        write(p12[1], &t, 1);   // send to child
        read(p21[0], &y, 1);    // wait for reply
    }

    // record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    close(p12[1]);
    close(p21[0]);
    waitpid(c, NULL, 0);

    // compute total and per-iteration cost
    double total_ns =
        (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    double roundtrip_ns = total_ns / (double)N;  // 1 parent->child->parent
    double per_switch_ns = roundtrip_ns / 2.0;   // about 2 switches each trip

    printf("N=%lld  total=%.0f ns\n", N, total_ns);
    printf("avg round-trip = %.2f ns (%.3f us)\n",
           roundtrip_ns, roundtrip_ns/1000.0);
    printf("~context switch ≈ %.2f ns (%.3f us) per switch\n",
           per_switch_ns, per_switch_ns/1000.0);

    return 0;
}
