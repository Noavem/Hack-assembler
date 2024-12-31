# Compiler
gcc = gcc

# Target executable
TARGET = main

# Source files
SRC = Assembler.c PearsonHashing.c HashMap.c SymbolTable.c Parser.c Code.c

# Compiler flags
CFLAGS = -Wall -g

# Build the target
$(TARGET):
	$(gcc) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)

.PHONY: clean