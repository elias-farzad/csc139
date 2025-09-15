// Elias Farzad
// This program creates two children and connects the standard output of one
// to the standard input of the other using the pipe() system call.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create the first child (writer)
    pid1 = fork();

    if (pid1 == 0) { // First child: ls -l
        // Close the unused read end of the pipe
        close(pipefd[0]);
        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        // Close the original write end of the pipe
        close(pipefd[1]);
        // Execute the command
        execlp("ls", "ls", "-l", NULL);
        // execlp only returns on error
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // Create the second child (reader)
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // Second child: wc -l
        // Close the unused write end of the pipe
        close(pipefd[1]);
        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        // Close the original read end of the pipe
        close(pipefd[0]);
        // Execute the command
        execlp("wc", "wc", "-l", NULL);
        // execlp only returns on error
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // Parent process
    // Close both ends of the pipe in the parent. This is crucial.
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children to terminate
    printf("Parent: Waiting for children to finish...\n");
    wait(NULL);
    wait(NULL);
    printf("Parent: Both children have finished.\n");

    return 0;
}
