// Elias Farzad
// This program inits a variable, then forks, then views the value of the variable in both processes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // init variables and fork
    int x = 100;
    int pid = fork();

    // child process
    if (pid == 0) {
        printf("Child process before changing x: %d\n", x);
        x = x + 1;
        printf("Child process before adding one to x: %d\n", x);
    } else { // parent process
        wait(NULL);
        printf("Parent process before changing x: %d\n", x);
        x = x + 2;
        printf("Parent process after adding 2 to x: %d\n", x);
    };
    
    return 0;
}
