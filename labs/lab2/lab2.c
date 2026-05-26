#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter program to run\n> ");
    fflush(stdout);

    if (getline(&line, &len, stdin) == -1) {
      break;
    }

    line[strcspn(line, "\n")] = '\0';

    pid_t pid = fork();
    if (pid == 0) {
      execl(line, line, NULL);
      printf("Exec failure\n");
      exit(1);
    } else {
      waitpid(pid, NULL, 0);
    }
  }

  free(line);
  return 0;
}
