CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -Iinclude
LDFLAGS = -lncurses

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

OUT = gcano
PREFIX ?= /usr/local

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(OUT)
	@echo "Installing gcano to $(PREFIX)/bin"
	install -Dm755 $(OUT) $(PREFIX)/bin/gcano

uninstall:
	@echo "Removing gcano from $(PREFIX)/bin"
	rm -f $(PREFIX)/bin/gcano

clean:
	rm -f src/*.o $(OUT)

.PHONY: all clean install uninstall
