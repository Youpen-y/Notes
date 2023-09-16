#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        // fork() failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child process
        printf("Child process is running...\n");
        sleep(5);
        printf("Child process is exiting...\n");
        exit(EXIT_SUCCESS);
    } else {
        // parent process
        printf("Parent process is waiting for child...\n");
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        }
        printf("Parent process is exiting...\n");
        exit(EXIT_SUCCESS);
    }
}
