CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lglfw -ldl -lm

SRC_DIR = src
LIB_DIR = libs
BUILD_DIR = build
BIN_DIR = bin

# Find all .c files
SRC = $(wildcard $(SRC_DIR)/*.c)
LIBSRC = $(wildcard $(LIB_DIR)/*.c)
ALLSRC = $(SRC) $(LIBSRC)

# Convert src/*.c → build/*.o
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(ALLSRC)))

TARGET = $(BIN_DIR)/app

# Default rule
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Compile each .c file into build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# Clean build/ and bin/
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

