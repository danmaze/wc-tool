CC=gcc
CFLAGS=-std=c99
SRC_DIR=src
TEST_DIR=tests

ccwc: $(SRC_DIR)/ccwc.c
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_DIR)/test_byte_count.c $(SRC_DIR)/ccwc.c
	$(CC) $(CFLAGS) -o test_byte_count $^
	./test_byte_count

clean:
	rm -f ccwc test_byte_count

.PHONY: clean test ccwc