// Elias Farzad
// This program forks then says hello in the child and goodbye in the parent, ensuring child runs first using wait()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // fork
    int pid = fork();

    // child process
    if (pid == 0) {
        printf("Hello\n");
    } else { // parent process
        pid_t rc = wait(NULL);
        printf("Goodbye\n");
        printf("%d", rc);
    };
    
    return 0;
}