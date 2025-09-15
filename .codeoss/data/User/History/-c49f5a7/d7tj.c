#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    int x = 100;
    int pid = fork();

    if (pid == 0) {
        printf("Child process before changing x: %d\n", x);
        x = x + 1;
        printf("Child process before adding one to x: %d\n")
    };

    wait(NULL)
    printf("Parent process before changing x: %d\n", x);
    x = x + 2;
    printf("Parent process after adding 2 to x: %d\n", x);
    
    return 0;
}
