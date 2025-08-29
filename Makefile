CC = gcc
CXX = g++
BIN = bin
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
IFLAGS = -Ilib/glfw/include -Ilib/glad/include 
LFLAGS = -Llib/glfw/build/src -Llib/glad/src/
LFLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
CXXFLAGS = -mmacosx-version-min=14.2

all: libs main

libs:
	cd lib/glfw/build && make
	cd lib/glad/ && $(CC) -o src/glad.o -c src/glad.c -Iinclude

src/%.o: src/%.c
	$(CXX) -o $@ -c $^ $(IFLAGS)

src/%.o: src/%.cpp
	$(CXX) -o $@ -c $^ $(IFLAGS)

main: src/main.o
	$(CXX) -o $(BIN)/main $^ lib/glad/src/glad.o $(LFLAGS) $(CXXFLAGS)

format:
	clang-format -i src/*.c src/*.h

clean:
	rm -f src/*.o bin/*
