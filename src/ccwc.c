#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include "ccwc.h"

FILE* open_file(const char* filename, const char* mode) {
  FILE* file = fopen(filename, mode);
  if (file == NULL) return NULL;
  return file;
}

int byte_count(const char *filename) {
  FILE *file = open_file(filename, "rb");
  if (!file) return -1;

  int byte_count = 0;
  char buffer[1024];
  size_t bytes_read;

  while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    byte_count += bytes_read;
  }
  if (ferror(file)) {
    fclose(file);
    return -1;
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
    if (ch == '\n') {
      line_count++;
    }
  }
  if (ferror(file)) {
    fclose(file);
    return -1;
  }

  fclose(file);
  return line_count;
}

int word_count(const char *filename) {
  FILE *file = open_file(filename, "r");
  if (!file) return -1;

  int word_count = 0;
  int in_word = 0;
  int ch;

  while ((ch = fgetc(file)) != EOF) {
    if (isspace(ch)) {
      in_word = 0;
    } else if (!in_word) {
      in_word = 1;
      word_count++;
    }
  }
  if (ferror(file)) {
    fclose(file);
    return -1;
  }

  fclose(file);
  return word_count;
}

int char_count(const char *filename) {
  setlocale(LC_CTYPE, "");

  FILE *file = open_file(filename, "r");
  if (!file) return -1;

  mbstate_t state = {0};
  int char_count = 0;
  char buffer[1024];
  size_t bytes_read;

  while((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    size_t i = 0;
    while (i < bytes_read) {
      int len = mbrlen(&buffer[i], bytes_read - i, &state);
      if (len == (size_t)-1) {
        fclose(file);
        return -1;
      } else if (len == (size_t)-2) {
        break;
      } else {
        i += (len > 0) ? len : 1;
        char_count++;
      }
    }
  }
  if (ferror(file)) {
    fclose(file);
    return -1;
  }

  fclose(file);
  return char_count;
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
  } else if (strcmp(argv[1], "-w") == 0) {
    result = word_count(argv[2]);
  } else if (strcmp(argv[1], "-m") == 0) {
    result = char_count(argv[2]);
  } else {
    fprintf(stderr, "Invalid option. Use -c for byte count, -l for line count, -w for word count, or -m for character count.\n");
    return 1;
  }

  if (result == -1) {
    fprintf(stderr, "Error processing file %s\n", argv[2]);
    return 1;
  } else {
    printf("  %d %s\n", result, argv[2]);
  }
  
  return 0;
}
#endif