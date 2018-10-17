CC=g++
LDFLAGS=-g -Wall -Wextra
SDLFLAGS=-lSDL2
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, bin/%.o, $(SRC))

.PHONY: clean all

all: tetris

tetris: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(SDLFLAGS) -o $@

bin/%.o: src/%.cpp
	$(CC) $(LDFLAGS) -c $< -o $@

clean:
	rm bin/*o tetris
