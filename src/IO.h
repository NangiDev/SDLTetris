#pragma once
#ifndef _IO_
#define _IO_

// ------ Includes -----

#include "SDL2/SDL.h"			
#include <iostream>

// ------ Enums -----

enum color { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX }; // Colors

class IO
{
public:

	IO();

	void DrawRectangle(SDL_Renderer*, int pX1, int pY1, int pX2, int pY2, enum color pC, int pPiece, int textureY=7);
    void DrawBoarder(SDL_Renderer*);
	void ClearScreen(SDL_Renderer*);
	int GetScreenHeight();
	int InitGraph();
	int Pollkey();
	int Getkey();
	int IsKeyDown(int pKey);
	void UpdateScreen(SDL_Renderer*);
    void Close();

private:

    void LoadTexture( std::string, SDL_Renderer*);

};

#endif // _IO_
