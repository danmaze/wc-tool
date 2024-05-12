#include "ccwc.h"

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

FILE *open_file(const char *filename, const char *mode) {
    if (filename == NULL || mode == NULL)
        return NULL;
    FILE *file = fopen(filename, mode);
    if (file == NULL)
        return NULL;
    return file;
}

void set_locale() {
    if (!getenv("LC_CTYPE") && !getenv("LC_ALL") && !getenv("LANG")) {
        setlocale(LC_CTYPE, "en_US.UTF-8");
    } else {
        setlocale(LC_CTYPE, "");
    }
}

int byte_count(const char *filename) {
    FILE *file = open_file(filename, "rb");
    if (!file)
        return -1;

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
    if (!file)
        return -1;

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
    set_locale();

    FILE *file = open_file(filename, "r");
    if (!file)
        return -1;

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
    set_locale();

    FILE *file = open_file(filename, "r");
    if (!file)
        return -1;

    mbstate_t state = {0};
    int char_count = 0;
    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
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

void print_result_or_error(int result, const char *filename) {
    if (result == -1) {
        fprintf(stderr, "Error processing file %s\n", filename);
    } else {
        printf("%8d %s\n", result, filename);
    }
}

void handle_default_option(const char *filename) {
    int num_lines = line_count(filename);
    int num_words = word_count(filename);
    int num_bytes = byte_count(filename);

    if (num_lines == -1 || num_words == -1 || num_bytes == -1) {
        print_result_or_error(-1, filename);
    }

    printf("%8d%8d%8d %s\n", num_lines, num_words, num_bytes, filename);
}

int handle_specific_option(char option, const char *filename) {
    switch (option) {
        case 'c':
            return byte_count(filename);
        case 'l':
            return line_count(filename);
        case 'w':
            return word_count(filename);
        case 'm':
            return char_count(filename);
        default:
            fprintf(stderr, "Invalid option. Use -c for byte count, -l for line count, -w for word count, or -m for character count.\n");
            return -1;
    }
}

#ifndef TEST_BUILD
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-c|-l|-w|-m] <filename>\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        handle_default_option(argv[1]);
        return 0;
    }

    int result = handle_specific_option(argv[1][1], argv[2]);
    print_result_or_error(result, argv[2]);

    return result == -1 ? 1 : 0;
}
#endif