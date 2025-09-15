// Elias Farzad
// This program forks then calls exec() to call /bin/ls
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int pid = fork();

    // child process
    if (pid == 0) {
        printf("child process\n");

        // execl("/bin/ls", "ls", NULL);

        /*
        char *myargs[] = {"ls", "-l", NULL};
        execv("/bin/ls", myargs);
        */

        /*
        char *envp[] = { "HOME=/tmp", NULL }; // custom environment
        execle("/bin/ls", "ls", "-l", NULL, envp);
        */

        // execlp("ls", "ls", "-l", NULL);

        /*
        char *myargs[] = {"ls", "-l", NULL};
        execvp("ls", myargs);
        */

        /*
        char *myargs[] = {"ls", "-l", NULL};
        char *envp[] = { NULL }; // empty environment
        execvpe("ls", myargs, envp);
        */

        // If exec returns, an error occurred
        fprintf(stderr, "exec failed\n");
        exit(1);
    } else {
        // parent process
        wait(NULL);
        printf("parent process\n");
    }

    return 0;

}