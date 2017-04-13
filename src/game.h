#pragma once
#ifndef _GAME_
#define _GAME_

// ------ Includes -----

#include "board.h"
#include "IO.h"
#include <time.h>

// ------ Defines -----

#define WAIT_TIME 700	

class Game
{
public:

	Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

	void DrawScene(SDL_Renderer*);
	void CreateNewPiece();

	int mPosX, mPosY;               // Position of the piece that is falling down
	int mPiece, mRotation;          // Kind and rotation the piece that is falling down

private:

	int mScreenHeight;              // Screen height in pixels
	int mNextPosX, mNextPosY;       // Position of the next piece
	int mNextPiece, mNextRotation;  // Kind and rotation of the next piece

	Board *mBoard;
	Pieces *mPieces;
	IO *mIO;

	int GetRand(int pA, int pB);
	void InitGame();
	void DrawPiece(SDL_Renderer*, int pX, int pY, int pPiece, int pRotation);
	void DrawBoard(SDL_Renderer*);
};

#endif // _GAME_