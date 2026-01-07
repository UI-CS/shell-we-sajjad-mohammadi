CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0
LDFLAGS = -lreadline
SRCDIR = .
BUILDDIR = ./build/Debug
TARGET = $(BUILDDIR)/shell

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/parse_input.c
OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/parse_input.o
HEADERS = $(SRCDIR)/shell.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(BUILDDIR)

debug: $(TARGET)
	gdb $(TARGET)
