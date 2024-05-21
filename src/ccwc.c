#include "ccwc.h"

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

FILE *open_file(const char *filename) {
    if (filename == NULL) return NULL;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return NULL;
    return file;
}

void set_locale() {
    if (!getenv("LC_CTYPE") && !getenv("LC_ALL") && !getenv("LANG")) {
        setlocale(LC_CTYPE, "en_US.UTF-8");
    } else {
        setlocale(LC_CTYPE, "");
    }
}

int byte_count(FILE *file) {
    if (!file) return -1;

    int byte_count = 0;
    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        byte_count += bytes_read;
    }
    if (ferror(file)) return -1;

    return byte_count;
}

int line_count(FILE *file) {
    if (!file) return -1;

    int line_count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') line_count++;
    }
    if (ferror(file)) return -1;

    return line_count;
}

int word_count(FILE *file) {
    set_locale();
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
    if (ferror(file)) return -1;

    return word_count;
}

int char_count(FILE *file) {
    set_locale();
    if (!file) return -1;

    mbstate_t state = {0};
    int char_count = 0;
    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size_t i = 0;
        while (i < bytes_read) {
            int len = mbrlen(&buffer[i], bytes_read - i, &state);
            if (len == (size_t)-1) return -1;
            if (len == (size_t)-2) break;   // next set of bytes are part of a possibly valid mb char
            i += (len > 0) ? len : 1;
            char_count++;
        }
    }
    if (ferror(file)) return -1;

    return char_count;
}

int count_all(FILE *file, int *line_count, int *word_count, int *byte_count, int *char_count) {
    /* added to support default option (multiple counting operations) in a single pass without
    needing to load the entire file into a large buffer when dealing with piped input which
    would be memory inefficient. Piped input is a non-seekable stream so invoking rewind after
    each individual count wouldn't work */

    set_locale();

    int in_word = 0;
    mbstate_t state = {0};
    char buffer[1024];
    size_t bytes_read;

    *line_count = 0;
    *word_count = 0;
    *byte_count = 0;
    *char_count = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        *byte_count += bytes_read;

        size_t i = 0;
        while (i < bytes_read) {
            int len = mbrlen(&buffer[i], bytes_read - i, &state);
            if (len == (size_t)-1) return -1;
            if (len == (size_t)-2) break;
            len = (len == 0) ? 1 : len;

            // Check each byte in the possible multibyte char
            for (size_t j = 0; j < len; j++) {
                if (buffer[i + j] == '\n') {
                    (*line_count)++;
                }

                if (isspace((unsigned char)buffer[i + j])) {
                    in_word = 0;
                } else if (!in_word) {
                    in_word = 1;
                    (*word_count)++;
                }
            }

            i += len;
            (*char_count)++;
        }
    }

    if (ferror(file)) {
        return -1;
    }

    return 0;
}

void print_result_or_error(int result, const char *filename) {
    if (result == -1) {
        fprintf(stderr, "Error processing %s\n", filename ? filename : "standard input");
    } else {
        printf("%8d %s\n", result, filename ? filename : "");
    }
}

void handle_default_option(FILE *file, const char *filename) {
    int num_lines, num_words, num_bytes, num_chars;
    int result = count_all(file, &num_lines, &num_words, &num_bytes, &num_chars);

    if (result == -1) {
        print_result_or_error(-1, filename);
    } else {
        printf("%8d%8d%8d %s\n", num_lines, num_words, num_bytes, filename ? filename : "");
    }
}

int get_count_for_specific_option(char option, FILE *file) {
    switch (option) {
        case 'c':
            return byte_count(file);
        case 'l':
            return line_count(file);
        case 'w':
            return word_count(file);
        case 'm':
            return char_count(file);
        default:
            fprintf(stderr, "Invalid option. Use -c for byte count, -l for line count, -w for word count, or -m for character count.\n");
            return -1;
    }
}

#ifndef TEST_BUILD
int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "Usage: %s [-c|-l|-w|-m] [filename]\n", argv[0]);
        return 1;
    }

    char *filename = NULL;
    FILE *input = stdin;  // default to standard input to support piping

    if (argc == 1) {
        // no arguments, read from stdin and use default behavior
        handle_default_option(input, NULL);
    } else if (argc == 2) {
        if (argv[1][0] == '-') {
            // an option is provided without filename, use stdin
            int result = get_count_for_specific_option(argv[1][1], input);
            print_result_or_error(result, NULL);
        } else {
            // a filename is provided without option
            filename = argv[1];
            input = open_file(filename);
            if (input == NULL) {
                fprintf(stderr, "Error opening file %s\n", filename);
                return 1;
            }
            handle_default_option(input, filename);
            fclose(input);
        }
    } else if (argc == 3) {
        // both option and filename are provided
        filename = argv[2];
        input = open_file(filename);
        if (input == NULL) {
            fprintf(stderr, "Error opening file %s\n", filename);
            return 1;
        }
        int result = get_count_for_specific_option(argv[1][1], input);
        print_result_or_error(result, filename);
        fclose(input);
    }

    return 0;
}
#endif