// Elias Farzad
// This program forks then says hello in the child and goodbye in the parent, ensuring the child runs first before the parent without wait()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // fork
    int pid = fork();

    // child process
    if (pid == 0) {
        printf("Hello");
    } else { // parent process
        wait(NULL); // this is necessary to ensure the child process runs first
        printf("Goodbye");
    };
    
    return 0;
}
