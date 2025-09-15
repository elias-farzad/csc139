// Elias Farzad
// This program creates a child process, and then in the child closes standard output
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    pid_t pid = fork();

    // child process
    if (pid == 0) {
        printf("this is the child process\n");
        // close standard output
        close(STDOUT_FILENO);
        // this should fail
        printf("This shouldn't print\n");
    } else { 
        // parent process
        wait(NULL);
        printf("This is the parent process\n");
    }
    
    return 0;
}
