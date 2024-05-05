#include <stdio.h>
#include "ccwc.h"

int tests_run = 0;
int tests_passed = 0;

void test_byte_count() {
  tests_run++;
  if (byte_count("test.txt") == 342190) {
    tests_passed++;
    printf("Test 'byte count' passed.\n");
  } else {
    printf("Test 'byte count' failed.\n");
  }
}

void test_line_count() {
  tests_run++;
  if (line_count("test.txt") == 7145) {
    tests_passed++;
    printf("Test 'line count' passed.\n");
  } else {
    printf("Test 'line count' failed.\n");
  }
}

int main() {
  putchar('\n');
  test_byte_count();
  test_line_count();
  printf("%d of %d tests passed.\n", tests_passed, tests_run);
  return tests_passed != tests_run;
}