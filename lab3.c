#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _POSTIX_C_SOURCE 200809L

#define HISTORY_SIZE 5

void add_to_history(char *history[], char *input);
void print_history(char *history[]);

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter input: ");
    if (getline(&line, &len, stdin) == -1) {
      break;
    }
    if (strncmp(line, "print\n", 6) == 0) {
      add_to_history(history, line);
      line = NULL;
      len = 0;
      print_history(history);
    } else {
      add_to_history(history, line);
      line = NULL;
      len = 0;
    }
  }

  free(line);
  return 0;
}

void add_to_history(char *history[], char *input) {
  free(history[0]);
  for (int i = 0; i < HISTORY_SIZE - 1; i++) {
    history[i] = history[i + 1];
  }
  history[HISTORY_SIZE - 1] = input;
}

void print_history(char *history[]) {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    if (history[i] != NULL) {
      printf("%s", history[i]);
    }
  }
}
