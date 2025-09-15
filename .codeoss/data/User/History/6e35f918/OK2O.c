// Elias Farzad
// This program creates a child process, and then in the child closes standard output (STDOUT_FILENO).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    pid_t pid = fork();

    // child process
    if (pid == 0) {
        printf("Child: This will be printed to standard output.\n");
        // close standard output
        close(STDOUT_FILENO);
        // this should fail
        printf("Child: This will NOT be printed.\n");
    } else { 
        // Parent process
        wait(NULL);
        printf("Parent: Child has terminated. Goodbye!\n");
    }
    
    return 0;
}
