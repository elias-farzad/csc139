#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    int x = 100;
    int pid = fork();

    if (pid == 0) {
        printf(x);
        x = x + 1;
        printf(x);
    } else {
        
    }
    
    return 0;
}
