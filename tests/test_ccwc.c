#include <stdio.h>
#include <string.h>

#include "ccwc.h"

#define TEST_DATA_DIR "tests/data"

int tests_run = 0;
int tests_passed = 0;

void print_test_result(int condition, const char* test_name) {
    tests_run++;
    if (condition) {
        printf("PASS: %s\n", test_name);
        tests_passed++;
    } else {
        printf("FAIL: %s\n", test_name);
    }
}

char* get_test_file_path(const char* filename) {
    static char path[1024];  // Not thread-safe but arguably better than dynamic mem alloc for this use case
    strcpy(path, TEST_DATA_DIR);
    strcat(path, "/");
    strcat(path, filename);
    return path;
}

void test_open_file_existing_file() {
    FILE* file = open_file(get_test_file_path("standard.txt"), "r");
    print_test_result(file != NULL, "open file with existing file");
    if (file) fclose(file);
}

void test_open_file_non_existing_file() {
    FILE* file = open_file(get_test_file_path("non_existing_file.txt"), "r");
    print_test_result(file == NULL, "open file with non existing file");
    if (file) fclose(file);  // Redundant if test passes but still good practice
}

void test_open_file_null_file_name() {
    print_test_result(open_file(NULL, "r") == NULL, "open file with null file name");
}

void test_open_file_invalid_mode() {
    FILE* file = open_file(get_test_file_path("standard.txt"), "invalide_mode");
    print_test_result(file == NULL, "open file with invalid mode");
    if (file) fclose(file);
}

void test_open_file_null_mode() {
    FILE* file = open_file(get_test_file_path("standard.txt"), NULL);
    print_test_result(file == NULL, "open file with null mode");
    if (file) fclose(file);
}

void test_byte_count_standard_file() {
    char* file_path = get_test_file_path("standard.txt");
    print_test_result(byte_count(file_path) == 342190, "byte count with standard file");
}

void test_byte_count_empty_file() {
    char* file_path = get_test_file_path("empty.txt");
    print_test_result(byte_count(file_path) == 0, "byte count with empty file");
}

void test_byte_count_single_char_file() {
    char* file_path = get_test_file_path("single_char.txt");
    print_test_result(byte_count(file_path) == 1, "byte count with single char file");
}

void test_byte_count_newline_file() {
    char* file_path = get_test_file_path("newline.txt");
    print_test_result(byte_count(file_path) == 1, "byte count with newline file");
}

void test_byte_count_unicode_file() {
    char* file_path = get_test_file_path("unicode.txt");
    print_test_result(byte_count(file_path) == 521, "byte count with unicode multibyte chars");
}

void test_byte_count_file_with_punctuation() {
    char* file_path = get_test_file_path("punctuation.txt");
    print_test_result(byte_count(file_path) == 271, "byte count with file with punctuation");
}

void test_byte_count_file_with_whitespaces() {
    char* file_path = get_test_file_path("whitespaces.txt");
    print_test_result(byte_count(file_path) == 202, "byte count with file with whitespaces");
}

void test_line_count_standard_file() {
    char* file_path = get_test_file_path("standard.txt");
    print_test_result(line_count(file_path) == 7145, "line count with standard file");
}

void test_line_count_single_line_file() {
    char* file_path = get_test_file_path("single_line.txt");
    print_test_result(line_count(file_path) == 1, "line count with single line file");
}

void test_line_count_empty_file() {
    char* file_path = get_test_file_path("empty.txt");
    print_test_result(line_count(file_path) == 0, "line count with empty file");
}

void test_line_count_multiple_lines_file() {
    char* file_path = get_test_file_path("multiple_lines.txt");
    print_test_result(line_count(file_path) == 17, "line count with multiple line file");
}

void test_line_count_empty_lines_file() {
    char* file_path = get_test_file_path("empty_lines.txt");
    print_test_result(line_count(file_path) == 7, "line count with empty lines file");
}

void test_line_count_file_with_punctuation() {
    char* file_path = get_test_file_path("punctuation.txt");
    print_test_result(line_count(file_path) == 9, "line count with file with punctuation");
}

void test_line_count_file_with_whitespaces() {
    char* file_path = get_test_file_path("whitespaces.txt");
    print_test_result(line_count(file_path) == 9, "line count with file with whitespaces");
}

void test_line_count_file_with_newlines_and_special_chars() {
    char* file_path = get_test_file_path("special_characters.txt");
    print_test_result(line_count(file_path) == 48, "line count with file with newlines and special chars");
}

void test_word_count_standard_file() {
    char* file_path = get_test_file_path("standard.txt");
    print_test_result(word_count(file_path) == 58164, "word count with standard file");
}

void test_word_count_empty_file() {
    char* file_path = get_test_file_path("empty.txt");
    print_test_result(word_count(file_path) == 0, "word count with empty file");
}

void test_word_count_single_word_file() {
    char* file_path = get_test_file_path("single_word.txt");
    print_test_result(word_count(file_path) == 1, "word count with single word file");
}

void test_word_count_single_char_file() {
    char* file_path = get_test_file_path("single_char.txt");
    print_test_result(word_count(file_path) == 1, "word count with single char file");
}

void test_word_count_multiple_lines_file() {
    char* file_path = get_test_file_path("multiple_lines.txt");
    print_test_result(word_count(file_path) == 276, "word count with multiple lines file");
}

void test_word_count_unicode_file() {
    char* file_path = get_test_file_path("unicode.txt");
    print_test_result(word_count(file_path) == 62, "word count with unicode file");
}

void test_word_count_file_with_punctuation() {
    char* file_path = get_test_file_path("punctuation.txt");
    print_test_result(word_count(file_path) == 41, "word count with file with punctuation");
}

void test_word_count_file_with_whitespaces() {
    char* file_path = get_test_file_path("whitespaces.txt");
    print_test_result(word_count(file_path) == 31, "word count with file with whitespaces");
}

void test_char_count_standard_file() {
    char* file_path = get_test_file_path("standard.txt");
    print_test_result(char_count(file_path) == 339292, "character count with standard file");
}

void test_char_count_empty_file() {
    char* file_path = get_test_file_path("empty.txt");
    print_test_result(char_count(file_path) == 0, "character count with empty file");
}

void test_char_count_single_word_file() {
    char* file_path = get_test_file_path("single_word.txt");
    print_test_result(char_count(file_path) == 5, "character count with single word file");
}

void test_char_count_single_char_file() {
    char* file_path = get_test_file_path("single_char.txt");
    print_test_result(char_count(file_path) == 1, "character count with single char file");
}

void test_char_count_single_line_file() {
    char* file_path = get_test_file_path("single_line.txt");
    print_test_result(char_count(file_path) == 116, "character count with single line file");
}

void test_char_count_multiple_lines_file() {
    char* file_path = get_test_file_path("multiple_lines.txt");
    print_test_result(char_count(file_path) == 1672, "character count with multiple lines file");
}

void test_char_count_file_with_punctuation() {
    char* file_path = get_test_file_path("punctuation.txt");
    print_test_result(char_count(file_path) == 265, "character count with file with punctuation");
}

void test_char_count_file_with_whitespaces() {
    char* file_path = get_test_file_path("whitespaces.txt");
    print_test_result(char_count(file_path) == 202, "character count with file with whitespaces");
}

void test_char_count_newlines_and_special_characters() {
    char* file_path = get_test_file_path("special_characters.txt");
    print_test_result(char_count(file_path) == 1124, "character count with newlines and special characters");
}

int main() {
    putchar('\n');

    test_open_file_existing_file();
    test_open_file_non_existing_file();
    test_open_file_null_file_name();
    test_open_file_invalid_mode();
    test_open_file_null_mode();

    test_byte_count_standard_file();
    test_byte_count_empty_file();
    test_byte_count_single_char_file();
    test_byte_count_newline_file();
    test_byte_count_unicode_file();
    test_byte_count_file_with_punctuation();
    test_byte_count_file_with_whitespaces();

    test_line_count_standard_file();
    test_line_count_single_line_file();
    test_line_count_empty_file();
    test_line_count_multiple_lines_file();
    test_line_count_empty_lines_file();
    test_line_count_file_with_punctuation();
    test_line_count_file_with_whitespaces();
    test_line_count_file_with_newlines_and_special_chars();

    test_word_count_standard_file();
    test_word_count_empty_file();
    test_word_count_single_word_file();
    test_word_count_single_char_file();
    test_word_count_multiple_lines_file();
    test_word_count_unicode_file();
    test_word_count_file_with_punctuation();
    test_word_count_file_with_whitespaces();

    test_char_count_standard_file();
    test_char_count_empty_file();
    test_char_count_single_word_file();
    test_char_count_single_char_file();
    test_char_count_single_line_file();
    test_char_count_multiple_lines_file();
    test_char_count_file_with_punctuation();
    test_char_count_file_with_whitespaces();
    test_char_count_newlines_and_special_characters();

    putchar('\n');
    printf("%d of %d tests passed.\n", tests_passed, tests_run);
    return tests_passed != tests_run;
}