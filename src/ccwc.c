#include <stdio.h>
#include <string.h>
#include "ccwc.h"

int ccwc_byte_count(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("File opening failed");
    return -1;
  }

  int count = 0;
  char buffer[1024];
  while (!feof(file)) {
    int bytes_read = fread(buffer, 1, sizeof(buffer), file);
    count += bytes_read;
  }

  fclose(file);
  return count;
}

#ifndef TEST_BUILD
int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s -c <filename>\n", argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "-c") == 0) {
    int byte_count = ccwc_byte_count(argv[2]);
    if (byte_count != -1) {
      printf("%d %s\n", byte_count, argv[2]);
    } else {
      return 1;
    }
  }

  return 0;
}
#endif