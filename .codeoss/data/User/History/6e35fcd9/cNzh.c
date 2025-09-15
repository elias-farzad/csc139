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

    // create a pipe before forking
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // create first child that will write
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // first child will call ls
        // close unused read end of pipe
        close(pipefd[0]);
        // redirect stdout to write end of pipe
        dup2(pipefd[1], STDOUT_FILENO);
        // close original write end of pipe
        close(pipefd[1]);
        // call exec
        execlp("ls", "ls", "-l", NULL);

        // execlp only returns on error
        perror("execlp ls");
        exit(EXIT_FAILURE);
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
        dup2(pipefd[0], STDIN_FILENO);
        // close original read end of pipe
        close(pipefd[0]);
        // call exec
        execlp("wc", "wc", "-l", NULL);

        // execlp only returns on error
        perror("execlp wc");
        exit(EXIT_FAILURE);
        
    } else { // parent process
    } else { // parent process (pid1 > 0 && pid2 > 0)

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
