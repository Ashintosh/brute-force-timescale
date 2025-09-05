CC       := gcc
CFLAGS   := -Iinclude -O2 -Wall
LDFLAGS  := 
EXE_NAME := bft

SRC_DIR  := src
OBJ_DIR  := bin/obj
BIN_DIR  := bin

TARGET   := $(BIN_DIR)/$(EXE_NAME)
SRC      := $(wildcard $(SRC_DIR)/*.c)
OBJ      := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean build artifacts
.PHONY: all clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
