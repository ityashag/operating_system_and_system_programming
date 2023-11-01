#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
    } else {
        // Parent process
        printf("before fork : %d\n", getpid());
        printf("I am the father : %d of child %d\n",getpid(),pid);
        printf("I am the child : %d\n",pid);
    }
    

    return 0;
}

