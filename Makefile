CC = gcc
BIN = bin
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
FLAGS = -Ilib/glfw/include -Ilib/glad/include -Llib/glfw/build/src -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
LFLAGS = lib/glad/src/glad.o

all: libs game

libs:
	cd lib/glfw/build && make
	cd lib/glad/ && $(CC) -o src/glad.o -c src/glad.c -Iinclude

game: $(OBJ)
	$(CC) -o $(BIN)/app $^ $(LFLAGS) $(FLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(FLAGS)

clean:
	rm -f src/*.o bin/*
