#pragma once
#ifndef _BOARD_
#define _BOARD_

#include "pieces.h"

#define BOARD_LINE_WIDTH 16
#define BLOCK_SIZE 16
#define BOARD_POSITION 16*6
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5

class Board
{
public:
	Board(Pieces *pPieces, int pScreenHeight);

	int GetXPosInPixels(int pPos);
	int GetYPosInPixels(int pPos);
	bool IsFreeBlock(int pX, int pY);
	bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
	void StorePiece(int pX, int pY, int pPiece, int pRotation);
    int GetColor( int pX, int pY );
	void DeletePossibleLines();
	bool IsGameOver();

private:

	enum { POS_FREE, POS_FILLED };
	int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
	int mColor[BOARD_WIDTH][BOARD_HEIGHT];
	Pieces *mPieces;
	int mScreenHeight;

	void InitBoard();
	void DeleteLine(int pY);
};
#endif // BOARD
