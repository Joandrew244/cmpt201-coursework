#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 128
#define BUF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    write(STDOUT_FILENO, "snprintf error\n", 15);
    _exit(1);
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *heap_start = sbrk(256);
  struct header *block1 = (struct header *)heap_start;
  struct header *block2 = (struct header *)((char *)heap_start + BLOCK_SIZE);

  block1->size = BLOCK_SIZE;
  block1->next = NULL;

  block2->size = BLOCK_SIZE;
  block2->next = block1;

  memset(block1 + 1, 0, BLOCK_SIZE - sizeof(struct header));
  memset(block2 + 1, 1, BLOCK_SIZE - sizeof(struct header));

  print_out("first block: %p\n", &block1, sizeof(void *));
  print_out("second block: %p\n", &block2, sizeof(void *));
  print_out("first block size: %lu\n", &block1->size, sizeof(uint64_t));
  print_out("first block next: %p\n", &block1->next, sizeof(void *));
  print_out("second block size: %lu\n", &block2->size, sizeof(uint64_t));
  print_out("second block next: %p\n", &block2->next, sizeof(void *));

  char *data1 = (char *)(block1 + 1);
  char *data2 = (char *)(block2 + 1);

  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); i++) {
    uint64_t val = (uint64_t)(unsigned char)data1[i];
    print_out("%lu\n", &val, sizeof(uint64_t));
  }

  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); i++) {
    uint64_t val = (uint64_t)(unsigned char)data2[i];
    print_out("%lu\n", &val, sizeof(uint64_t));
  }

  return 0;
}
