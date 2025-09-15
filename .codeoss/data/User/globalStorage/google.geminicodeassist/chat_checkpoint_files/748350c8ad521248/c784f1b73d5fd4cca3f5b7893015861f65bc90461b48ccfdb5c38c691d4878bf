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

        exec("/bin/ls");

        // --- execl() ---
        // 'l': list of arguments
        // 'p': (not present) path to executable must be absolute/relative
        // 'e': (not present) environment inherited from parent
        // execl("/bin/ls", "ls", NULL);


        // --- execv() ---
        // 'v': vector (array) of arguments
        // 'p': (not present) path must be absolute/relative
        // 'e': (not present) environment inherited
        /*
        char *myargs[] = {"ls", "-l", NULL};
        execv("/bin/ls", myargs);
        */

        // --- execle() ---
        // 'l': list of arguments
        // 'p': (not present) path must be absolute/relative
        // 'e': environment passed explicitly
        /*
        char *envp[] = { "HOME=/tmp", NULL }; // custom environment
        execle("/bin/ls", "ls", "-l", NULL, envp);
        */

        // --- execlp() ---
        // 'l': list of arguments
        // 'p': executable is searched in PATH
        // 'e': (not present) environment inherited
        // execlp("ls", "ls", "-l", NULL);


        // --- execvp() ---
        // 'v': vector (array) of arguments
        // 'p': executable is searched in PATH
        // 'e': (not present) environment inherited
        /*
        char *myargs[] = {"ls", "-l", NULL};
        execvp("ls", myargs);
        */

        // --- execvpe() --- (GNU extension)
        // 'v': vector (array) of arguments
        // 'p': executable is searched in PATH
        // 'e': environment passed explicitly
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