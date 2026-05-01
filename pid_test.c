#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv){

    pid_t pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Fork Failed");
        return (1);
    }
    else if (pid1 == 0) {
        printf("Child process: %d\n", getpid());
    }
    else {
        sleep(5);
        printf("Parent process: %d\n", getpid());
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        fprintf(stderr, "Fork Failed");
        return (1);
    }
    else if (pid2 == 0) {
        printf("Child process 2: %d\n", getpid());
    }
    else {
        sleep(5);
        printf("Parent process 2: %d\n", getpid());
    }

    int pid1_status = waitpid(pid1, NULL, WNOHANG);
    if (pid1_status == -1) {
        fprintf(stderr, "Waitpid Failed for pid1\n");
        return (1);
    }

    // wait(NULL);

    return (0);
}
