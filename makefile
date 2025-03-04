# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/local/include

# Directories
SRC_DIR = src
TEST_DIR = src/tests
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source and Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
SOURCES = $(SRC_FILES) $(TEST_FILES)

# Convert source file paths to object file paths
OBJ_FILES = $(patsubst src/%.cpp, $(OBJ_DIR)/src/%.o, $(SRC_FILES))
OBJ_FILES += $(patsubst tests/%.cpp, $(OBJ_DIR)/tests/%.o, $(TEST_FILES))

# Executable name
TARGET = $(BIN_DIR)/test_option

# Default target
all: setup $(TARGET)

# Create necessary directories
setup:
	mkdir -p $(OBJ_DIR)/src $(OBJ_DIR)/tests $(BIN_DIR)

# Compile source files into object files
$(OBJ_DIR)/src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create the final executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Run the executable
run: all
	./$(TARGET)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)
