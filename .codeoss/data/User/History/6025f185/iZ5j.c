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
        printf("Child process writing\n");
        char *message = "Child process written\n";
        write(file_descriptor, message, strlen(message));
        printf("finished writing to child\n");
    } else { // parent process
        wait(NULL);
        printf("Parent process: Writing to file...\n");
        const char *parent_message = "Hello from parent!\n";
        write(file_descriptor, parent_message, strlen(parent_message));
        printf("Parent process: Finished writing.\n");
    }

    // Close the file descriptor
    close(ffile_descriptord);

    return 0;
}
