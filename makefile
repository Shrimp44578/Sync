# Compiler and flags
CC = icx
CFLAGS = -Wall -Wextra -O2 -fPIC -I./include  # Add -I./include to include header files
SRC = ./src/Sync.c ./src/PrintFunctions.c ./src/SyncNetwork.c
OBJ = $(SRC:./src/%.c=./obj/%.o)  # Convert .c files to .o files
BIN = ./bin/Sync
LIB_SRC = ./src/get_defines.c  # Source file for the shared library
LIB_SO = ./lib/libexample.so      # Target location for the shared library

# Default target
all: $(BIN) $(LIB_SO)

# Link object files to create the binary
$(BIN): $(OBJ)
	@echo "Linking object files to create the binary..."
	@mkdir -p ./bin
	@$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

# Compile each source file into an object file
./obj/%.o: ./src/%.c
	@echo "Compiling $<..."
	@mkdir -p ./obj
	@$(CC) $(CFLAGS) -c $< -o $@

# Build the shared library
$(LIB_SO): $(LIB_SRC)
	@echo "Building shared library $@..."
	@mkdir -p ./lib
	@$(CC) $(CFLAGS) -shared -o $@ $<

# Clean the binary, object files, and shared library
clean:
	@echo "Cleaning up generated files..."
	@rm -f $(BIN) $(OBJ) $(LIB_SO)

# Phony targets to avoid conflicts with files named "clean", etc.
.PHONY: all clean