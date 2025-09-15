#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    int x = 100;
    int pid = fork();

    if (pid == 0) {
        printf("%d", x);
        x = x + 1;
        printf("%d", x);
    } else {

    }
    
    return 0;
}
