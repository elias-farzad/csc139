// Elias Farzad
// This program opens a file, then forks, then both parent and child write to the file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // open/create file and fork
    int file_descriptor = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    int pid = fork();

    // child process
    if (pid == 0) {
        printf("child process writing\n");
        char *message = "child process written\n";
        write(file_descriptor, message, strlen(message));
        printf("finished writing from child\n");
    } else { // parent process
        wait(NULL);
        printf("parent process writing\n");
        char *message = "parent process written\n";
        write(file_descriptor, message, strlen(message));
        printf("finished writing from parent\n");
    }

    // close the file descriptor
    close(file_descriptor);

    return 0;
}
