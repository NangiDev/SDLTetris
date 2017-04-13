#include "IO.h"
#include <stdio.h>
#include <iostream>

static Uint32 mColors[COLOR_MAX][3] = { { 0, 0, 0 },
{ 255, 0, 0 },{ 0, 255, 0 },{ 0, 0, 255 },
{ 255, 255, 0 },{ 255, 0, 255 },{ 0, 255, 255 },
{ 255, 255, 255 } };

IO::IO()
{
	InitGraph();
}

void IO::ClearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, mColors[BLACK][0], mColors[BLACK][1], mColors[BLACK][2], 255);
	SDL_RenderClear(renderer);
}

void IO::DrawRectangle(SDL_Renderer* renderer, int pX1, int pY1, int pX2, int pY2, enum color pC)
{
	SDL_SetRenderDrawColor(renderer, mColors[pC][0], mColors[pC][1], mColors[pC][2], 255);
	SDL_Rect rectangle;

	rectangle.x = pX1;
	rectangle.y = pY1;
	rectangle.w = pX2;
	rectangle.h = pY2 - 1;
	SDL_RenderFillRect(renderer, &rectangle);
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
