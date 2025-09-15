// Elias Farzad
// This program forks then says hello in the child and goodbye in the parent, ensuring child runs first using waitpid()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // fork
    pid_t pid = fork();

    // child process
    if (pid == 0) {
        printf("Child pid: %d\n", getpid());
        printf("Hello\n");
    } else { // parent process
        // wait for the specific child to terminate
        pid_t rc = waitpid(pid, NULL, 0);
        printf("Parent pid: %d\n", getpid());
        printf("Goodbye\n");
        printf("%d\n", rc);
    };
    
    return 0;
}