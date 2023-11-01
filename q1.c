#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipe_fd[2]; // Pipe file descriptors
    char input_string[BUFFER_SIZE];
    char concatenated_string[BUFFER_SIZE * 2];
    
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid == 0) { // P2 process
        close(pipe_fd[1]); // Close the write end of the pipe in P2
        
        // Read the string from P1
        read(pipe_fd[0], input_string, BUFFER_SIZE);
        close(pipe_fd[0]);
        
        // Concatenate the received string with another string
        char additional_string[] = " (concatenated in P2)";
        int input_len = strlen(input_string);
        int additional_len = strlen(additional_string);
        
        // Concatenate manually without using string functions
        int i, j;
        for (i = 0; i < input_len; i++) {
            concatenated_string[i] = input_string[i];
        }
        for (j = 0; j < additional_len; j++) {
            concatenated_string[input_len + j] = additional_string[j];
        }
        
        concatenated_string[input_len + additional_len] = '\0'; // Null-terminate the concatenated string
        
        // Send the concatenated string back to P1
        write(pipe_fd[1], concatenated_string, strlen(concatenated_string) + 1);
        close(pipe_fd[1]);
    } else { // P1 process
        close(pipe_fd[0]); // Close the read end of the pipe in P1
        
        printf("Enter a string: ");
        fgets(input_string, BUFFER_SIZE, stdin);
        input_string[strlen(input_string) - 1] = '\0'; // Remove the newline character
        
        // Send the string to P2
        write(pipe_fd[1], input_string, strlen(input_string) + 1);
        close(pipe_fd[1]);
        
        // Wait for P2 to send back the concatenated string
        wait(NULL);
        
        // Read the concatenated string from P2 and print it
        read(pipe_fd[0], concatenated_string, BUFFER_SIZE * 2);
        printf("Concatenated string received from P2: %s\n", concatenated_string);
        close(pipe_fd[0]);
    }
    
    return 0;
}
