// Elias Farzad
// This program creates a child process, and then in the child closes standard output (STDOUT_FILENO).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child: This will be printed to standard output.\n");
        
        // Close standard output
        close(STDOUT_FILENO);
        
        // This printf will fail to write to the terminal because stdout is closed.
        printf("Child: This will NOT be printed.\n");
    } else { 
        // Parent process
        wait(NULL);
        printf("Parent: Child has terminated. Goodbye!\n");
    }
    
    return 0;
}
