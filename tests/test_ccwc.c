#include <stdio.h>
#include "ccwc.h"

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

void test_open_file_existing_file() {
  print_test_result(open_file("test.txt", "r") != NULL, "open file with existing file");
}

void test_open_file_non_existing_file() {
  print_test_result(open_file("non_existing_file.txt", "r") == NULL, "open file with non existing file");
}

void test_open_file_null_file_name() {
  print_test_result(open_file(NULL, "r") == NULL, "open file with null file name");
}

void test_open_file_invalid_mode() {
  print_test_result(open_file("test.txt", "invalide_mode") == NULL, "open file with invalid mode");
}

void test_open_file_null_mode() {
  print_test_result(open_file("test.txt", NULL) == NULL, "open file with null mode");
}

void test_byte_count() {
    print_test_result(byte_count("test.txt") == 342190, "byte count");
}

void test_line_count() {
    print_test_result(line_count("test.txt") == 7145, "line count");
}

void test_word_count() {
    print_test_result(word_count("test.txt") == 58164, "word count");
}

void test_char_count() {
    print_test_result(char_count("test.txt") == 339292, "character count");
}

int main() {
    putchar('\n');
    test_open_file_existing_file();
    test_open_file_non_existing_file();
    test_open_file_null_file_name();
    test_open_file_invalid_mode();
    test_open_file_null_mode();
    test_byte_count();
    test_line_count();
    test_word_count();
    test_char_count();
    printf("%d of %d tests passed.\n", tests_passed, tests_run);
    return tests_passed != tests_run;
}