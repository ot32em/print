CC=g++
CFLAGS=-std=c++11

TEST_CC=$(CC) $(CFLAGS)
TEST_INCLUDE=-Ilib/bandit \
			 -Isrc
TEST_SRC=$(wildcard test/*Test.cpp)

TEST_BIN=tester.out
TEST_BIN_DIR=test_build
TEST_BIN_PATH=$(TEST_BIN_DIR)/$(TEST_BIN)

all:

test: test_only test_clean


test_only: test_env
	@$(TEST_CC) $(TEST_INCLUDE) $(TEST_SRC) -o $(TEST_BIN_PATH)
	@./$(TEST_BIN_PATH)

test_env:
	@mkdir -p $(TEST_BIN_DIR)

test_clean:
	@rm -rf $(TEST_BIN_DIR)
