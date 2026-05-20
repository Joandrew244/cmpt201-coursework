#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buffer = NULL;
  size_t size = 0;
  char *mark;
  char *token;

  while (1) {
    printf("Please enter some text: ");
    ssize_t chars = getline(&buffer, &size, stdin);
    if (chars < 0) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    printf("Tokens:\n");
    token = strtok_r(buffer, " ", &mark);
    while (token != NULL) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " ", &mark);
    }
  }

  free(buffer);

  return 0;
}
