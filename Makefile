CC = gcc
BIN = bin
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
IFLAGS = -Ilib/glfw/include -Ilib/glad/include 
LFLAGS = -Llib/glfw/build/src -Llib/glad/src/ -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

all: libs game

libs:
	cd lib/glfw/build && make
	cd lib/glad/ && $(CC) -o src/glad.o -c src/glad.c -Iinclude

src/main.o: src/main.c
	$(CC) -o src/main.o -c src/main.c $(IFLAGS)

game: $(OBJ)
	$(CC) -o $(BIN)/app $^ lib/glad/src/glad.o $(LFLAGS)

clean:
	rm -f src/*.o bin/*
