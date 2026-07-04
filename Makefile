CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -Iinclude
LDFLAGS = -lncurses

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

OUT = gcano

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(OUT)

.PHONY: all clean
