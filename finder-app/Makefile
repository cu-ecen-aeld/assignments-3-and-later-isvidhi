# Makefile for writer application
# Default compiler
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror

# Target executable
TARGET = writer

# Source files
SRC = writer.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o