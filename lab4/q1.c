#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
  int pipefd[2];
  char string1[100], string2[100];

  // Create a pipe
  pipe(pipefd);

  // Fork a child process
  pid_t pid = fork();

  if (pid == 0) {
    // This is the child process

    // Read the string from the pipe
    read(pipefd[0], string1, sizeof(string1));

    // Concatenate the string with another string
    strcat(string1, ", world!");

    // Write the concatenated string back to the pipe
    write(pipefd[1], string1, sizeof(string1));

    exit(0);
  } else {
    // This is the parent process

    // Write a string to the pipe
    printf("Enter a string: ");
    scanf("%s", string1);
    write(pipefd[1], string1, sizeof(string1));

    // Read the concatenated string from the pipe
    read(pipefd[0], string2, sizeof(string2));

    // Print the concatenated string
    printf("The concatenated string is: %s\n", string2);
  }

  return 0;
}
