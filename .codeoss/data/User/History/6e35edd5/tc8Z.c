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
        printf("hello, I am child (pid:%d)\n", (int) getpid());

        // The exec() family of functions replaces the current process image
        // with a new process image. If an exec() function is successful,
        // it does not return. A return indicates an error.
        //
        // Uncomment one of the following blocks to test a specific exec variant.

        // --- execl() ---
        // 'l': list of arguments
        // 'p': (not present) path to executable must be absolute/relative
        // 'e': (not present) environment inherited from parent
        // execl("/bin/ls", "ls", "-l", NULL);


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
        execlp("ls", "ls", "-l", NULL);


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
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
    }
    return 0;
}
