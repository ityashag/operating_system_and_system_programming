#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void alarm_handler(int signal) {
  // This function is called when the alarm goes off

  printf("The alarm has gone off!\n");
}

int main() {
  // Get the time from the user
  int time_to_wait;
  printf("How long do you want to wait (in seconds)? ");
  scanf("%d", &time_to_wait);

  // Set up the alarm
  signal(SIGALRM, alarm_handler);
  alarm(time_to_wait);

  // Allow the user to execute other programs
  printf("The timer is running. You can execute other programs now.\n");

  // Wait for the alarm to go off
  pause();

  return 0;
}
