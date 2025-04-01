# Compiler and flags
CC = icx
GCC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = ./src/Sync.c ./src/PrintFunctions.c ./src/SyncNetwork.c
OBJ = $(SRC:./src/%.c=./obj/%.o)  # Convert .c files to .o files
BIN = ./bin/Sync

# Default target
all: $(BIN)

# Link object files to create the binary
$(BIN): $(OBJ)
	@echo "Linking object files to create the binary..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

# Compile each source file into an object file
./obj/%.o: ./src/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean the binary and object files
clean:
	@echo "Cleaning up generated files..."
	@rm -f $(BIN) $(OBJ)

# Phony targets to avoid conflicts with files named "clean", etc.
.PHONY: all clean