#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  // Create a file named my_file.txt
  FILE *fp = fopen("my_file.txt", "w");
  fprintf(fp, "Child 1 reads this line\n");
  fprintf(fp, "Child 2 reads this line\n");
  fprintf(fp, "Child 3 reads this line\n");
  fprintf(fp, "Child 4 reads this line\n");
  fclose(fp);

  // Fork four child processes
  pid_t pids[4];
  for (int i = 0; i < 4; i++) {
    pids[i] = fork();
    if (pids[i] == 0) {
      // This is a child process

      // Read a line from the file
      FILE *fp = fopen("my_file.txt", "r");
      char line[100];
      fgets(line, sizeof(line), fp);
      fclose(fp);

      // Print the line
      printf("Child %d: %s\n", i + 1, line);
      exit(0);
    }
  }

  // Wait for the child processes to finish
  for (int i = 0; i < 4; i++) {
    waitpid(pids[i], NULL, 0);
  }

  return 0;
}
