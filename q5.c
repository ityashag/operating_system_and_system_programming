#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int num1 = 10, num2 = 5;

    pid_t add_pid = fork();

    if (add_pid < 0) {
        perror("Fork for addition error");
    } else if (add_pid == 0) {
        // Child process for addition
        int result = num1 + num2;
        printf("Addition result: %d\n", result);
    } else {
        pid_t sub_pid = fork();

        if (sub_pid < 0) {
            perror("Fork for subtraction error");
        } else if (sub_pid == 0) {
            // Child process for subtraction
            int result = num1 - num2;
            printf("Subtraction result: %d\n", result);
        } else {
            pid_t mul_pid = fork();

            if (mul_pid < 0) {
                perror("Fork for multiplication error");
            } else if (mul_pid == 0) {
                // Child process for multiplication
                int result = num1 * num2;
                printf("Multiplication result: %d\n", result);
            } else {
                // Parent process
                pid_t div_pid = fork();

                if (div_pid < 0) {
                    perror("Fork for division error");
                } else if (div_pid == 0) {
                    // Child process for division
                    if (num2 != 0) {
                        float result = (float) num1 / num2;
                        printf("Division result: %.2f\n", result);
                    } else {
                        printf("Division by zero is not allowed.\n");
                    }
                } else {
                    // Parent process
                    for (int i = 0; i < 4; i++) {
                        wait(NULL); // Wait for each child process to complete
                    }
                }
            }
        }
    }

    return 0;
}
