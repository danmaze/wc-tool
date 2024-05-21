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
    FILE* file = open_file(get_test_file_path("standard.txt"));
    print_test_result(file != NULL, "open file with existing file");
    if (file) fclose(file);
}

void test_open_file_non_existing_file() {
    FILE* file = open_file(get_test_file_path("non_existing_file.txt"));
    print_test_result(file == NULL, "open file with non-existing file");
    if (file) fclose(file);  // Redundant if test passes but still good practice
}

void test_open_file_null_file_name() {
    print_test_result(open_file(NULL) == NULL, "open file with null file name");
}

void test_byte_count_null_file() {
    print_test_result(byte_count(NULL) == -1, "byte count with null file");
}

void test_byte_count_standard_file() {
    FILE* file = open_file(get_test_file_path("standard.txt"));
    if (file) {
        print_test_result(byte_count(file) == 342190, "byte count with standard file");
        fclose(file);
    }
}

void test_byte_count_empty_file() {
    FILE* file = open_file(get_test_file_path("empty.txt"));
    if (file) {
        print_test_result(byte_count(file) == 0, "byte count with empty file");
        fclose(file);
    }
}

void test_byte_count_single_char_file() {
    FILE* file = open_file(get_test_file_path("single_char.txt"));
    if (file) {
        print_test_result(byte_count(file) == 1, "byte count with single char file");
        fclose(file);
    }
}

void test_byte_count_newline_file() {
    FILE* file = open_file(get_test_file_path("newline.txt"));
    if (file) {
        print_test_result(byte_count(file) == 1, "byte count with newline file");
        fclose(file);
    }
}

void test_byte_count_unicode_file() {
    FILE* file = open_file(get_test_file_path("unicode.txt"));
    if (file) {
        print_test_result(byte_count(file) == 521, "byte count with unicode multibyte chars");
        fclose(file);
    }
}

void test_byte_count_file_with_punctuation() {
    FILE* file = open_file(get_test_file_path("punctuation.txt"));
    if (file) {
        print_test_result(byte_count(file) == 271, "byte count with file with punctuation");
        fclose(file);
    }
}

void test_byte_count_file_with_whitespaces() {
    FILE* file = open_file(get_test_file_path("whitespaces.txt"));
    if (file) {
        print_test_result(byte_count(file) == 202, "byte count with file with whitespaces");
        fclose(file);
    }
}

void test_line_count_null_file() {
    print_test_result(line_count(NULL) == -1, "line count with null file");
}

void test_line_count_standard_file() {
    FILE* file = open_file(get_test_file_path("standard.txt"));
    if (file) {
        print_test_result(line_count(file) == 7145, "line count with standard file");
        fclose(file);
    }
}

void test_line_count_single_line_file() {
    FILE* file = open_file(get_test_file_path("single_line.txt"));
    if (file) {
        print_test_result(line_count(file) == 1, "line count with single line file");
        fclose(file);
    }
}

void test_line_count_empty_file() {
    FILE* file = open_file(get_test_file_path("empty.txt"));
    if (file) {
        print_test_result(line_count(file) == 0, "line count with empty file");
        fclose(file);
    }
}

void test_line_count_multiple_lines_file() {
    FILE* file = open_file(get_test_file_path("multiple_lines.txt"));
    if (file) {
        print_test_result(line_count(file) == 17, "line count with multiple line file");
        fclose(file);
    }
}

void test_line_count_empty_lines_file() {
    FILE* file = open_file(get_test_file_path("empty_lines.txt"));
    if (file) {
        print_test_result(line_count(file) == 7, "line count with empty lines file");
        fclose(file);
    }
}

void test_line_count_file_with_punctuation() {
    FILE* file = open_file(get_test_file_path("punctuation.txt"));
    if (file) {
        print_test_result(line_count(file) == 9, "line count with file with punctuation");
        fclose(file);
    }
}

void test_line_count_file_with_whitespaces() {
    FILE* file = open_file(get_test_file_path("whitespaces.txt"));
    if (file) {
        print_test_result(line_count(file) == 9, "line count with file with whitespaces");
        fclose(file);
    }
}

void test_line_count_file_with_newlines_and_special_chars() {
    FILE* file = open_file(get_test_file_path("special_characters.txt"));
    if (file) {
        print_test_result(line_count(file) == 48, "line count with file with newlines and special chars");
        fclose(file);
    }
}

void test_word_count_null_file() {
    print_test_result(word_count(NULL) == -1, "word count with null file");
}

void test_word_count_standard_file() {
    FILE* file = open_file(get_test_file_path("standard.txt"));
    if (file) {
        print_test_result(word_count(file) == 58164, "word count with standard file");
        fclose(file);
    }
}

void test_word_count_empty_file() {
    FILE* file = open_file(get_test_file_path("empty.txt"));
    if (file) {
        print_test_result(word_count(file) == 0, "word count with empty file");
        fclose(file);
    }
}

void test_word_count_single_word_file() {
    FILE* file = open_file(get_test_file_path("single_word.txt"));
    if (file) {
        print_test_result(word_count(file) == 1, "word count with single word file");
        fclose(file);
    }
}

void test_word_count_single_char_file() {
    FILE* file = open_file(get_test_file_path("single_char.txt"));
    if (file) {
        print_test_result(word_count(file) == 1, "word count with single char file");
        fclose(file);
    }
}

void test_word_count_multiple_lines_file() {
    FILE* file = open_file(get_test_file_path("multiple_lines.txt"));
    if (file) {
        print_test_result(word_count(file) == 276, "word count with multiple lines file");
        fclose(file);
    }
}

void test_word_count_unicode_file() {
    FILE* file = open_file(get_test_file_path("unicode.txt"));
    if (file) {
        print_test_result(word_count(file) == 62, "word count with unicode file");
        fclose(file);
    }
}

void test_word_count_file_with_punctuation() {
    FILE* file = open_file(get_test_file_path("punctuation.txt"));
    if (file) {
        print_test_result(word_count(file) == 41, "word count with file with punctuation");
        fclose(file);
    }
}

void test_word_count_file_with_whitespaces() {
    FILE* file = open_file(get_test_file_path("whitespaces.txt"));
    if (file) {
        print_test_result(word_count(file) == 31, "word count with file with whitespaces");
        fclose(file);
    }
}

void test_char_count_null_file() {
    print_test_result(char_count(NULL) == -1, "character count with null file");
}

void test_char_count_standard_file() {
    FILE* file = open_file(get_test_file_path("standard.txt"));
    if (file) {
        print_test_result(char_count(file) == 339292, "character count with standard file");
        fclose(file);
    }
}

void test_char_count_empty_file() {
    FILE* file = open_file(get_test_file_path("empty.txt"));
    if (file) {
        print_test_result(char_count(file) == 0, "character count with empty file");
        fclose(file);
    }
}

void test_char_count_single_word_file() {
    FILE* file = open_file(get_test_file_path("single_word.txt"));
    if (file) {
        print_test_result(char_count(file) == 5, "character count with single word file");
        fclose(file);
    }
}

void test_char_count_single_char_file() {
    FILE* file = open_file(get_test_file_path("single_char.txt"));
    if (file) {
        print_test_result(char_count(file) == 1, "character count with single char file");
        fclose(file);
    }
}

void test_char_count_single_line_file() {
    FILE* file = open_file(get_test_file_path("single_line.txt"));
    if (file) {
        print_test_result(char_count(file) == 116, "character count with single line file");
        fclose(file);
    }
}

void test_char_count_multiple_lines_file() {
    FILE* file = open_file(get_test_file_path("multiple_lines.txt"));
    if (file) {
        print_test_result(char_count(file) == 1672, "character count with multiple lines file");
        fclose(file);
    }
}

void test_char_count_file_with_punctuation() {
    FILE* file = open_file(get_test_file_path("punctuation.txt"));
    if (file) {
        print_test_result(char_count(file) == 265, "character count with file with punctuation");
        fclose(file);
    }
}

void test_char_count_file_with_whitespaces() {
    FILE* file = open_file(get_test_file_path("whitespaces.txt"));
    if (file) {
        print_test_result(char_count(file) == 202, "character count with file with whitespaces");
        fclose(file);
    }
}

void test_char_count_newlines_and_special_characters() {
    FILE* file = open_file(get_test_file_path("special_characters.txt"));
    if (file) {
        print_test_result(char_count(file) == 1124, "character count with newlines and special characters");
        fclose(file);
    }
}

void test_count_all_null_file() {
    int lines, words, bytes, chars;
    print_test_result(count_all(NULL, &lines, &words, &bytes, &chars) == -1, "count_all with null file");
}

void test_count_all_standard_file() {
    FILE* file = open_file(get_test_file_path("standard.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 7145 && words == 58164 && bytes == 342190 && chars == 339292,
            "count_all with standard file");
        fclose(file);
    }
}

void test_count_all_empty_file() {
    FILE* file = open_file(get_test_file_path("empty.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 0 && words == 0 && bytes == 0 && chars == 0,
            "count_all with empty file");
        fclose(file);
    }
}

void test_count_all_single_word_file() {
    FILE* file = open_file(get_test_file_path("single_word.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 0 && words == 1 && bytes == 5 && chars == 5,
            "count_all with single word file");
        fclose(file);
    }
}

void test_count_all_single_char_file() {
    FILE* file = open_file(get_test_file_path("single_char.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 0 && words == 1 && bytes == 1 && chars == 1,
            "count_all with single char file");
        fclose(file);
    }
}

void test_count_all_multiple_lines_file() {
    FILE* file = open_file(get_test_file_path("multiple_lines.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 17 && words == 276 && bytes == 1672 && chars == 1672,
            "count_all with multiple lines file");
        fclose(file);
    }
}

void test_count_all_unicode_file() {
    FILE* file = open_file(get_test_file_path("unicode.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 17 && words == 62 && bytes == 521 && chars == 384,
            "count_all with unicode file");
        fclose(file);
    }
}

void test_count_all_file_with_punctuation() {
    FILE* file = open_file(get_test_file_path("punctuation.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 9 && words == 41 && bytes == 271 && chars == 265,
            "count_all with file with punctuation");
        fclose(file);
    }
}

void test_count_all_file_with_whitespaces() {
    FILE* file = open_file(get_test_file_path("whitespaces.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 9 && words == 31 && bytes == 202 && chars == 202,
            "count_all with file with whitespaces");
        fclose(file);
    }
}

void test_count_all_newlines_and_special_characters() {
    FILE* file = open_file(get_test_file_path("special_characters.txt"));
    if (file) {
        int lines, words, bytes, chars;
        int result = count_all(file, &lines, &words, &bytes, &chars);
        print_test_result(
            result == 0 && lines == 48 && words == 135 && bytes == 1124 && chars == 1124,
            "count_all with newlines and special characters");
        fclose(file);
    }
}

int main() {
    putchar('\n');

    test_open_file_existing_file();
    test_open_file_non_existing_file();
    test_open_file_null_file_name();

    test_byte_count_null_file();
    test_byte_count_standard_file();
    test_byte_count_empty_file();
    test_byte_count_single_char_file();
    test_byte_count_newline_file();
    test_byte_count_unicode_file();
    test_byte_count_file_with_punctuation();
    test_byte_count_file_with_whitespaces();

    test_line_count_null_file();
    test_line_count_standard_file();
    test_line_count_single_line_file();
    test_line_count_empty_file();
    test_line_count_multiple_lines_file();
    test_line_count_empty_lines_file();
    test_line_count_file_with_punctuation();
    test_line_count_file_with_whitespaces();
    test_line_count_file_with_newlines_and_special_chars();

    test_word_count_null_file();
    test_word_count_standard_file();
    test_word_count_empty_file();
    test_word_count_single_word_file();
    test_word_count_single_char_file();
    test_word_count_multiple_lines_file();
    test_word_count_unicode_file();
    test_word_count_file_with_punctuation();
    test_word_count_file_with_whitespaces();

    test_char_count_null_file();
    test_char_count_standard_file();
    test_char_count_empty_file();
    test_char_count_single_word_file();
    test_char_count_single_char_file();
    test_char_count_single_line_file();
    test_char_count_multiple_lines_file();
    test_char_count_file_with_punctuation();
    test_char_count_file_with_whitespaces();
    test_char_count_newlines_and_special_characters();

    test_count_all_null_file();
    test_count_all_standard_file();
    test_count_all_empty_file();
    test_count_all_single_word_file();
    test_count_all_single_char_file();
    test_count_all_multiple_lines_file();
    test_count_all_unicode_file();
    test_count_all_file_with_punctuation();
    test_count_all_file_with_whitespaces();
    test_count_all_newlines_and_special_characters();

    putchar('\n');
    printf("%d of %d tests passed.\n", tests_passed, tests_run);
    return tests_passed != tests_run;
}
