#include <stdio.h>
#include <string.h>
#include "ccwc.h"

FILE* open_file(const char* filename, const char* mode) {
  FILE* file = fopen(filename, mode);
  if (file == NULL) {
    perror("File opening failed");
    return NULL;
  }
  return file;
}

int byte_count(const char *filename) {
  FILE *file = open_file(filename, "rb");
  if (!file) return -1;

  int byte_count = 0;
  char buffer[1024];
  while (!feof(file)) {
    int bytes_read = fread(buffer, 1, sizeof(buffer), file);
    if (ferror(file)) {
      fclose(file);
      return -1;
    }
    byte_count += bytes_read;
  }

  fclose(file);
  return byte_count;
}

int line_count(const char *filename) {
  FILE *file = open_file(filename, "r");
  if (!file) return -1;

  int line_count = 0;
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ferror(file)) {
      fclose(file);
      return -1;
    }
    if (ch == '\n') {
      line_count++;
    }
  }
  

  fclose(file);
  return line_count;
}

#ifndef TEST_BUILD
int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s -c <filename>\n", argv[0]);
    return 1;
  }

  int result = 0;
  if (strcmp(argv[1], "-c") == 0) {
    result = byte_count(argv[2]);
  } else if (strcmp(argv[1], "-l") == 0) {
    result = line_count(argv[2]);
  } else {
    fprintf(stderr, "Invalid option. Use -c for byte count or -l for line count.\n");
    return 1;
  }

  if (result == -1) {
    fprintf(stderr, "Error processing file %s\n", argv[2]);
    return 1;
  } else {
    printf("%d %s\n", result, argv[2]);
  }
  
  return 0;
}
#endif