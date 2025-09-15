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

    // create first child that will write
    pid1 = fork();

    if (pid1 == 0) { // first child will call ls
        // close unused read end of pipe
        close(pipefd[0]);
        // redirect stdout to write end of pipe
        dup2(pipefd[1], STDOUT_FILENO);
        // close original write end of pipe
        close(pipefd[1]);
        // call exec
        execlp("ls", "ls", NULL);

        // execlp only returns on error
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // create second child that will read
    pid2 = fork();

    if (pid2 == 0) { // second child will call wc
        // close unused write end of pipe
        close(pipefd[1]);
        // redirect stdout to read end of pipe
        dup2(pipefd[0], STDIN_FILENO);
        // close original read end of pipe
        close(pipefd[0]);
        // call exec
        execl("/bin/ls", "wc", NULL);

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
