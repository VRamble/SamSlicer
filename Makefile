# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR = src
BUILD_DIR = build
TARGET = main

# Source files and object files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean