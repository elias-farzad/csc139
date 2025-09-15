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
        sleep(1); // used sleep instead of wait to ensure child runs first
        printf("Goodbye\n");
    };
    
    return 0;
}