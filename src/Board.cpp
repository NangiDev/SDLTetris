
#include "pieces.h"
#include "board.h"

Board::Board(Pieces *pPieces, int pScreenHeight)
{
	// Get the screen height
	mScreenHeight = pScreenHeight;

	// Get the pointer to the pieces class
	mPieces = pPieces;

	//Init the board blocks with free positions
	InitBoard();
}

void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = POS_FREE;
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
	// Store each block of the piece into the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			// Store only the blocks of the piece that are not holes
			if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
				mBoard[i1][j1] = POS_FILLED;
		}
	}
}

bool Board::IsGameOver()
{
	//If the first line has blocks, then, game over
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == POS_FILLED) return true;
	}

	return false;
}

void Board::DeleteLine(int pY)
{
	// Moves all the upper lines one row down
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j - 1];
		}
	}
}

void Board::DeletePossibleLines()
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == BOARD_WIDTH) DeleteLine(j);
	}
}

bool Board::IsFreeBlock(int pX, int pY)
{
	if (mBoard[pX][pY] == POS_FREE) return true; else return false;
}

int Board::GetXPosInPixels(int pPos)
{
	return  ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pPos)
{
	return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation)
{
	// Checks collision with pieces already stored in the board or the board limits
	// This is just to check the 5x5 blocks of a piece with the appropriate area in the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			// Check if the piece is outside the limits of the board
			if (i1 < 0 ||
				i1 > BOARD_WIDTH - 1 ||
				j1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
					return 0;
			}

			// Check if the piece have collisioned with a block already stored in the map
			if (j1 >= 0)
			{
				if ((mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock(i1, j1)))
					return false;
			}
		}
	}

	// No collision
	return true;
}