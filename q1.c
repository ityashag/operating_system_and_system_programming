#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
int main() {
    FILE *procatt0, *procatt1;
    procatt0 = fopen("procatt0.txt", "w");
    procatt1 = fopen("procatt1.txt", "w");

    if (procatt0 == NULL || procatt1 == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    pid_t pid;

    // Iterate through processes
    for (pid = 1;pid<=2; pid++) {
        // Fork to create a child process
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            // Gather process attributes and write to appropriate file

            // a. PID
            fprintf(procatt0, "PID: %d\n", getpid());
            fprintf(procatt1, "PID: %d\n", getpid());

            // b. PPID
            fprintf(procatt0, "PPID: %d\n", getppid());
            fprintf(procatt1, "PPID: %d\n", getppid());

            // c. Nice number
            int nice_value = nice(0);
            fprintf(procatt0, "Nice: %d\n", nice_value);
            fprintf(procatt1, "Nice: %d\n", nice_value);

            // d. TTY
            fprintf(procatt0, "TTY: %s\n", ttyname(STDIN_FILENO));
            fprintf(procatt1, "TTY: %s\n", ttyname(STDIN_FILENO));

            // e. User name of RUID and EUID
            struct rusage usage;
            getrusage(RUSAGE_SELF, &usage);
            fprintf(procatt0, "Real User: %s\n", getlogin());
            fprintf(procatt0, "Effective User: %s\n", getlogin());
            fprintf(procatt1, "Real User: %s\n", getlogin());
            fprintf(procatt1, "Effective User: %s\n", getlogin());

            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            int status;
            waitpid(child_pid, &status, 0);

            // Check if we've reached the maximum number of processes
            if (pid >= 10) {
                break;
            }
        }
    }

    fclose(procatt0);
    fclose(procatt1);

    return 0;
}

