CC	= gcc
STD	= c99
CFLAGS	= -std=$(STD) \
	  -Os -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables \
	  -Wall -Wextra -pedantic -I./src \
	  -march=native
LDFLAGS	= -lraylib -lm -ldl -lpthread -lrt -lX11 -lGL
SRC	= $(wildcard src/*.c)
OBJ	= $(SRC:.c=.o)
BIN	= danmaku

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ) $(BIN)

.PHONY: clean
