CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -Iinclude
LDFLAGS = -lncurses

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

OUT = gcano
PREFIX ?= /usr/local

all: $(OUT)

$(OUT): $(OBJ)
	@$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

install: $(OUT)
	@echo "Installing gcano..."
	@install -Dm755 $(OUT) $(PREFIX)/bin/gcano
	@echo "Done."

uninstall:
	@echo "Removing gcano..."
	@rm -f $(PREFIX)/bin/gcano
	@echo "Done."

clean:
	@rm -f src/*.o $(OUT)

.PHONY: all clean install uninstall
