// Elias Farzad
// This program measures the average cost of a simple system call

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv) {
    // times to run the syscall
    long long N = (argc > 1) ? atoll(argv[1]) : 1000000LL;

    // open /dev/null (special file that discards all data)
    int fd = open("/dev/null", O_RDONLY);
    if (fd < 0) { perror("open"); return 1; }

    // record start time
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // run sys call in a loop
    for (long long i = 0; i < N; i++) read(fd, NULL, 0);

    // record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    close(fd);

    // compute time in nanoseconds
    double total_ns =
        (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);

    // Print total and average per system call
    printf("N=%lld  total=%.0f ns  avg=%.2f ns (%.3f us)\n",
           N, total_ns, total_ns / N, (total_ns / N) / 1000.0);
    return 0;
}
