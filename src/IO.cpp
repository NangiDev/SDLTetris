#include "IO.h"
#include <stdio.h>
#include <iostream>
#include "SDL2/SDL_image.h"
#include "board.h"

static Uint32 mColors[COLOR_MAX][3] = { { 0, 0, 0 },
{ 255, 0, 0 },{ 0, 255, 0 },{ 0, 0, 255 },
{ 255, 255, 0 },{ 255, 0, 255 },{ 0, 255, 255 },
{ 255, 255, 255 } };

SDL_Texture* gTexture = NULL;
SDL_Rect gTextureRect;
SDL_Rect gTextureRectSize;

IO::IO(){
    gTextureRect.x = 0;
    gTextureRect.y = 7*8;
    gTextureRect.w = 8;
    gTextureRect.h = 8;

    gTextureRectSize.x = 0;
    gTextureRectSize.y = 0;
    gTextureRectSize.w = BLOCK_SIZE;
    gTextureRectSize.h = BLOCK_SIZE;

	InitGraph();
}

void IO::ClearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, mColors[BLACK][0], mColors[BLACK][1], mColors[BLACK][2], 255);
	SDL_RenderClear(renderer);
}

bool success = true;
void IO::DrawRectangle(SDL_Renderer* renderer, int pX1, int pY1, int pX2, int pY2, enum color pC, int pPiece, int textureY)
{
	SDL_SetRenderDrawColor(renderer, mColors[pC][0], mColors[pC][1], mColors[pC][2], 255);
	SDL_Rect rectangle;

	rectangle.x = pX1;
	rectangle.y = pY1;
	rectangle.w = pX2;
	rectangle.h = pY2 - 1;
    gTextureRectSize.x = pX1;
    gTextureRectSize.y = pY1;
    gTextureRect.x = pPiece*8;
    gTextureRect.y = textureY*8;
	SDL_RenderFillRect(renderer, &rectangle);

    if( gTexture == NULL && success)
    {
        LoadTexture( "assets/tiles.png", renderer);
        if( gTexture == NULL )
        {
            printf( "Failed to load texture image!\n" );
            success = false;
        }
    }
    else
    {
        SDL_RenderCopy( renderer, gTexture, &gTextureRect, &gTextureRectSize );
    }
}

void IO::DrawBoarder( SDL_Renderer* renderer )
{
    // Game Board limiters
    for ( int x = BLOCK_SIZE; x <= BLOCK_SIZE * BOARD_WIDTH; x += BLOCK_SIZE )
    {
        IO::DrawRectangle(renderer, x, 0, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 5, 0);
        IO::DrawRectangle(renderer, x, BLOCK_SIZE * BOARD_HEIGHT, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 2, 0);
    }
    for ( int y = BLOCK_SIZE; y < BLOCK_SIZE * BOARD_HEIGHT; y += BLOCK_SIZE )
    {
        IO::DrawRectangle(renderer, 0, y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 0, 0);
        IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE, y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 7, 0);
    }
    // Game Board corners
    IO::DrawRectangle(renderer, 0, 0, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 4, 0);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE, 0, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 6, 0);
    IO::DrawRectangle(renderer, 0, BLOCK_SIZE * BOARD_HEIGHT, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 1, 0);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE, BLOCK_SIZE * BOARD_HEIGHT, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 3, 0);

    //Next piece boarder
    for ( int x = BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 3; x <= BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 8; x += BLOCK_SIZE )
    {
        IO::DrawRectangle(renderer, x, 0, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 5, 1);
        IO::DrawRectangle(renderer, x, BLOCK_SIZE * 8, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 2, 1);
    }
    for ( int y = BLOCK_SIZE; y < BLOCK_SIZE * 8; y += BLOCK_SIZE )
    {
        IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 2, y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 0, 1);
        IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 9, y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 7, 1);
    }
    // Next piece corners
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 2, 0, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 4, 1);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 9, 0, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 6, 1);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 2, BLOCK_SIZE * 8, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 1, 1);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 9, BLOCK_SIZE * 8, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 3, 1);

    //Score boarder
    for ( int x = BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 3; x <= BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 8; x += BLOCK_SIZE )
    {
        IO::DrawRectangle(renderer, x, BLOCK_SIZE * BOARD_HEIGHT - BLOCK_SIZE * 8, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 5, 1);
        IO::DrawRectangle(renderer, x, BLOCK_SIZE * BOARD_HEIGHT, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 2, 1);
    }
    for ( int y = BLOCK_SIZE * BOARD_HEIGHT - BLOCK_SIZE * 7; y < BLOCK_SIZE * BOARD_HEIGHT; y += BLOCK_SIZE )
    {
        IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 2, y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 0, 1);
        IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 9, y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 7, 1);
    }
    // Score corners
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 2, BLOCK_SIZE * BOARD_HEIGHT - BLOCK_SIZE * 8, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 4, 1);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 9, BLOCK_SIZE * BOARD_HEIGHT - BLOCK_SIZE * 8, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 6, 1);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 2, BLOCK_SIZE * BOARD_HEIGHT, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 1, 1);
    IO::DrawRectangle(renderer, BLOCK_SIZE * BOARD_WIDTH + BLOCK_SIZE * 9, BLOCK_SIZE * BOARD_HEIGHT, BLOCK_SIZE - 1, BLOCK_SIZE - 1, BLUE, 3, 1);
}

int IO::GetScreenHeight()
{
	return 480;
}

void IO::UpdateScreen(SDL_Renderer* renderer)
{
	SDL_RenderPresent(renderer);
}

int IO::Pollkey()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			return event.key.keysym.sym;
		case SDL_QUIT:
			exit(3);
		}
	}
	return -1;
}

int IO::Getkey()
{
	SDL_Event event;
	while (true)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
			break;
		if (event.type == SDL_QUIT)
			exit(3);
	};
	return event.key.keysym.sym;
}

int IO::IsKeyDown(int pKey)
{
	const Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyboardState(&mNumkeys);
	return mKeytable[pKey];
}

int IO::InitGraph()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
	return 0;
}

void IO::LoadTexture ( std::string path, SDL_Renderer* renderer)
{
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        gTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( gTexture == NULL )
        {
            printf( "Unablet to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( loadedSurface );
    }
}

void IO::Close()
{
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;
    IMG_Quit();
}
