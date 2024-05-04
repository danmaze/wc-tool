CC=gcc
CFLAGS=-Iinclude -std=c99
SRC_DIR=src
TEST_DIR=tests
BUILD_DIR=build

OBJS_MAIN=${BUILD_DIR}/ccwc.o
OBJS_TEST=${BUILD_DIR}/test_byte_count.o ${BUILD_DIR}/ccwc_test.o

all: ccwc test

ccwc: $(OBJS_MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/ccwc_test.o: $(SRC_DIR)/ccwc.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_BUILD -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJS_TEST)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_byte_count $^
	./$(BUILD_DIR)/test_byte_count

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/ccwc $(BUILD_DIR)/test_byte_count ccwc

.PHONY: clean test ccwc all