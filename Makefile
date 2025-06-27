# Makefile for building the main executable

# Compiler to use
CC = clang

# Compiler flags:
# -Wall: Enable all standard warnings
# -Wextra: Enable extra warnings (more verbose than -Wall)
# -Werror: Treat warnings as errors
# -std=c99: Specify the C standard (C99 in this case)
# -g: Include debugging information
CFLAGS = -Wall -Wextra -Werror -std=c23 -g -fsanitize=address

# Linker flags (none in this simple example, but good to have for future expansion)
LDFLAGS = -fsanitize=address

# Source files
SRCS = main.c

# Object files (generated from source files)
# The `patsubst` function substitutes .c with .o in the SRCS list
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Name of the executable
TARGET = main

# Phony targets:
# .PHONY tells make that these are not actual files
# all: The default target, builds the executable
# clean: Removes generated files
.PHONY: all clean run

# Default target: builds the executable
all: $(TARGET)

# Rule to link the executable from object files
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Rule to compile .c files into .o files
# $@: The name of the target (e.g., main.o)
# $<: The name of the first prerequisite (e.g., main.c)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up generated files
clean:
	$(RM) $(OBJS) $(TARGET)

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)
