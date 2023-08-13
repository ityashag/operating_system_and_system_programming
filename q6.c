#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    FILE *file1, *file2;

    file1 = fopen("file1.txt", "w");
    file2 = fopen("file2.txt", "w");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            if (i == 0) {
                // First child in the pair
                fprintf(file1, "Hello from Child 1!");
                fclose(file1);
            } else if (i == 1) {
                // Second child in the pair
                fprintf(file2, "Hi from Child 2!");
                fclose(file2);
            }
            exit(EXIT_SUCCESS);
        }else
	{
		sleep(3);
	}
    }

    for (int i = 0; i < 2; i++) {
        // Parent process
        char buffer[50];
        FILE *file;
        if (i == 0) {
            // Read from file1
            file = fopen("file1.txt", "r");
            fgets(buffer, sizeof(buffer), file);
            printf("Parent received from Child 1: %s\n", buffer);
            fclose(file);
        } else if (i == 1) {
            // Read from file2
            file = fopen("file2.txt", "r");
            fgets(buffer, sizeof(buffer), file);
            printf("Parent received from Child 2: %s\n", buffer);
            fclose(file);
        }
    }

    for (int i = 0; i < 2; i++) {
        wait(NULL); // Wait for all child processes to complete
    }

    return 0;
}
