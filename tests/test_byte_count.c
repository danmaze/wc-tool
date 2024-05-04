#include <stdio.h>

int tests_run = 0;
int tests_passed = 0;

void test_byte_count() {
  tests_run++;
  if (ccwc_byte_count("test.txt") == 342190) {
    tests_passed++;
    printf("Test 'byte count' passed.\n");
  } else {
    printf("Test 'byte count' failed.\n");
  }
}

int main() {
  test_byte_count();
  printf("%d of %d tests passed.\n", tests_passed, tests_run);
  return tests_passed != tests_run;
}