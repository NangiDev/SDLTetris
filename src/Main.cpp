 #include "game.h"
#include <stdio.h>
#include <iostream>
#include "SDL2\include\SDL.h"

int main(int argc, char* argv[]) 
{

	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();

	// Pieces
	Pieces mPieces;

	// Board
	Board mBoard(&mPieces, mScreenHeight);

	// Game
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

	// Get the actual clock milliseconds (SDL)
	unsigned long mTime1 = SDL_GetTicks();

	SDL_Window *window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return EXIT_FAILURE;

	window = SDL_CreateWindow(
		"Tetris with SDL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0
	);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	// ----- Main Loop -----

	while (!mIO.IsKeyDown(SDLK_ESCAPE))
	{
		// ----- Draw -----

		mIO.ClearScreen(renderer); 		// Clear screen
		mGame.DrawScene(renderer);		// Draw stuff
		mIO.UpdateScreen(renderer);		// Put the graphic context in the screen

								// ----- Input -----

		int mKey = mIO.Pollkey();

		switch (mKey)
		{
		case (SDLK_RIGHT):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX++;
			break;
		}

		case (SDLK_LEFT):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX--;
			break;
		}

		case (SDLK_DOWN):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
				mGame.mPosY++;
			break;
		}

		case (SDLK_x):
		{
			// Check collision from up to down
			while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

			mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

			mBoard.DeletePossibleLines();

			if (mBoard.IsGameOver())
			{
				std::cout << "Game Over!!" << std::endl;
				mIO.Getkey();
				exit(0);
			}

			mGame.CreateNewPiece();

			SDL_Delay(WAIT_TIME);
			break;
		}

		case (SDLK_z):
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
				mGame.mRotation = (mGame.mRotation + 1) % 4;

			break;
		}
		}

		// ----- Vertical movement -----

		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}

	return 0;
}
