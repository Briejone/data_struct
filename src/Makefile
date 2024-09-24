# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -O0 --coverage
LDFLAGS = --coverage
AR = ar
ARFLAGS = rcs

# Directories
BUILD_DIR = ../build
COV_DIR = ../coverage
HTML_DIR = ../coverage-html

# Source files
LIB_SRCS = array.cpp dlist.cpp hash_table.cpp list.cpp queue.cpp stack.cpp tree.cpp
TEST_SRCS = array_test.cpp dlist_test.cpp hash_table_test.cpp list_test.cpp queue_test.cpp stack_test.cpp tree_test.cpp
MAIN_SRC = main_test.cpp

# Object files
LIB_OBJS = $(LIB_SRCS:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.cpp=$(BUILD_DIR)/%.o)
MAIN_OBJ = $(BUILD_DIR)/main_test.o

# Static library
LIB_NAME = libmylib.a

# Test executable
TEST_EXEC = test_exec

# Default target
all: $(TEST_EXEC)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build static library
$(BUILD_DIR)/$(LIB_NAME): $(LIB_OBJS) | $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

# Build library object files
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build test object files
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build main test object file
$(MAIN_OBJ): $(MAIN_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link test executable with main and library
$(TEST_EXEC): $(TEST_OBJS) $(MAIN_OBJ) $(BUILD_DIR)/$(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(MAIN_OBJ) $(TEST_OBJS) $(BUILD_DIR)/$(LIB_NAME) -lgtest -lgtest_main -pthread

# Run tests and generate gcov reports
test: $(TEST_EXEC)
	./$(TEST_EXEC)
	@mkdir -p $(COV_DIR)
	@for file in $(LIB_SRCS); do \
	    gcov -o $(BUILD_DIR) $$file; \
	done
	@mv *.gcov $(COV_DIR)

# Generate HTML coverage report
coverage-html: test
	lcov --capture --directory $(BUILD_DIR) --output-file $(COV_DIR)/coverage.info
	lcov --remove $(COV_DIR)/coverage.info '/usr/*' --output-file $(COV_DIR)/coverage.info
	lcov --remove $(COV_DIR)/coverage.info '*/test/*' --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(HTML_DIR)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TEST_EXEC) *.gcda *.gcno $(COV_DIR) $(HTML_DIR) *.bin

# Clean everything
distclean: clean
	rm -f $(BUILD_DIR)/$(LIB_NAME)

.PHONY: all clean distclean test coverage-html
