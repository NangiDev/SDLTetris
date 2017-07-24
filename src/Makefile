All: compile

compile: Main.o Board.o Game.o IO.o Pieces.o
	g++ -Wall -g Main.o Board.o Game.o IO.o Pieces.o -L. -lSDL2 -o tetris

Main.o: Main.cpp
	g++ -c Main.cpp

Board.o:
	g++ -c Board.cpp

Game.o:
	g++ -c Game.cpp

IO.o:
	g++ -c IO.cpp

Pieces.o:
	g++ -c Pieces.cpp

clean:
	rm -rf *o tetris
