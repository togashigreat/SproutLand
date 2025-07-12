# Define the executable name
TARGET = main

# Source files
SRCS = main.c


# external packages
PKGS = raylib 

# Compiler (gcc or clang)
CC = clang

# Compiler flags
CFLAGS = -Wall -Wextra -march=native

# Linker flags (using pkg-config for simplicity and portability)
LDFLAGS = $(shell pkg-config --cflags --libs $(PKGS))

# Default rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Clean up compiled files
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
