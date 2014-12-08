CC=g++
CFLAGS=-std=c++11

TEST_CC=$(CC) $(CFLAGS)
TEST_INCLUDE=-Ilib/bandit \
			 -Isrc

TEST_BIN=tester.out
TEST_BIN_DIR=test_build
TEST_BIN_PATH=$(TEST_BIN_DIR)/$(TEST_BIN)

BTEST_SRC=$(wildcard test/functional/*Test.cpp)
UTEST_SRC=$(widlcard test/unit/*Test.cpp)

all:

btest: btest_only test_clean

btest_only: test_env
ifneq "$(BTEST_SRC)" ""
	@$(TEST_CC) $(TEST_INCLUDE) $(BTEST_SRC) -o $(TEST_BIN_PATH)
	@./$(TEST_BIN_PATH)
else
	$(info No functional tests found...)
endif

utest: utest_only test_clean

utest_only: test_env
ifneq ("$(UTEST_SRC)", "")
	$(TEST_CC) $(TEST_INCLUDE) $(UTEST_SRC) -o $(TEST_BIN_PATH)
	@./$(TEST_BIN_PATH)
else
	$(info No unit tests found...)
endif

test_env:
	@mkdir -p $(TEST_BIN_DIR)

test_clean:
	@rm -rf $(TEST_BIN_DIR)
