CC=g++
CFLAGS=-std=c++11

TEST_CC=$(CC) $(CFLAGS)
TEST_INCLUDE=-Ilib/bandit \
			 -Isrc

TEST_BIN=tester.out
TEST_BIN_DIR=test_build
TEST_BIN_PATH=$(TEST_BIN_DIR)/$(TEST_BIN)

TEST_SRC_DIR=test
TEST_RUNNER=$(TEST_SRC_DIR)/runner.cpp
BTEST_SRC=$(wildcard $(TEST_SRC_DIR)/functional/*Test.cpp) $(TEST_RUNNER)
UTEST_SRC=$(widlcard $(TEST_SRC_DIR)/unit/*Test.cpp) $(TEST_RUNNER)

all:

btest: btest_only test_clean

btest_only: test_env
	@$(TEST_CC) $(TEST_INCLUDE) $(BTEST_SRC) -o $(TEST_BIN_PATH)
	@./$(TEST_BIN_PATH)

utest: utest_only test_clean

utest_only: test_env
	@$(TEST_CC) $(TEST_INCLUDE) $(UTEST_SRC) -o $(TEST_BIN_PATH)
	@./$(TEST_BIN_PATH)

test_env:
	@mkdir -p $(TEST_BIN_DIR)

test_clean:
	@rm -rf $(TEST_BIN_DIR)
