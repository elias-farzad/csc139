// Elias Farzad
// This program creates two children and connects the standard output of one to the standard input of the other using the pipe() system call.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    // create a pipe before forking
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // create first child that will write
    pid1 = fork();

    if (pid1 == 0) { // first child will call ls
        // close unused read end of pipe
        close(pipefd[0]);
        // redirect stdout to write end of pipe
        dup2(pipefd[1], STDOUT_FILENO);
        // close original write end of pipe
        // close original write end of pipe now that it's duplicated
        close(pipefd[1]);
        // call exec
        execlp("ls", "ls", "-l", NULL);

        // execlp only returns on error
        perror("execlp ls");
        exit(EXIT_FAILURE);
        // Child 1 writes a simple message to its stdout (the pipe)
        printf("Hello from the first child!");

        exit(EXIT_SUCCESS);
    }

    // create second child that will read
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // second child will call wc

        // close unused write end of pipe
        close(pipefd[1]);
        // redirect stdout to read end of pipe
        // redirect stdin to read end of pipe
        dup2(pipefd[0], STDIN_FILENO);
        // close original read end of pipe
        // close original read end of pipe now that it's duplicated
        close(pipefd[0]);
        // call exec
        execlp("wc", "wc", "-l", NULL);

        // execlp only returns on error
        perror("execlp wc");
        exit(EXIT_FAILURE);
        
        // Child 2 reads from its stdin (the pipe) and prints to its stdout (the terminal)
        char buffer[128];
        ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            printf("Second child received: '%s'\n", buffer);
        }

        exit(EXIT_SUCCESS);
    } else { // parent process

        // close both ends of pipe in parent process
        close(pipefd[0]);
        close(pipefd[1]);

        // Wait for both children to terminate
        printf("parent process waiting for children to finish\n");
        wait(NULL);
        wait(NULL);
        printf("parent process after children finished\n");
    }

    return 0;
}
