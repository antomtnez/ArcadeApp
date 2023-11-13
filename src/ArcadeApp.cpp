#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>

#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Star2D.h"
#include "Square2D.h"
#include "ChessBoard.h"

using namespace std;

const int SCREEN_HEIGHT = 288;
const int SCREEN_WIDTH = 224;
const int MAGNIFICATION = 3;

int main(int argv, char** args)
{
	Screen theScreen;

	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Vec2D centerPoint(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	Vec2D endPoint(SCREEN_WIDTH/2, 0);

	/*
	Line2D line = {centerPoint, endPoint};
	Star2D star(line, 15);

	Square2D square(50, centerPoint);
	Square2D square2(100, centerPoint);

	theScreen.Draw(square2, Color::Green(), 6.28 / 2);
	theScreen.Draw(star, Color::Yellow());
	theScreen.Draw(square, Color::Pink());
	*/

	ChessBoard theChessBoard(24);

	theScreen.DrawChessTable(theChessBoard, Vec2D(0, 0));

	theScreen.SwapScreens();

	SDL_Event sdlEvent;
	bool running = true;

	while(running)
	{
		while(SDL_PollEvent(&sdlEvent))
		{
			switch(sdlEvent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	return 0;
}