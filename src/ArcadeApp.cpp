#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>

#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Star2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"


using namespace std;

const int SCREEN_HEIGHT = 288;
const int SCREEN_WIDTH = 224;
const int MAGNIFICATION = 3;

std::vector<Star2D> CreateTenStars()
{
	std::vector<Star2D> stars;

	std::random_device r;
	std::default_random_engine randEng(r());
	std::uniform_int_distribution<int> uniform_Size_dist(5, 30);
	std::uniform_int_distribution<int> uniform_Height_dist(30, SCREEN_HEIGHT - 30);
	std::uniform_int_distribution<int> uniform_Width_dist(30, SCREEN_WIDTH - 30);

	for(int i = 0; i < 10; i++)
	{
		stars.push_back(Star2D(Vec2D(uniform_Width_dist(randEng), uniform_Height_dist(randEng)), uniform_Size_dist(randEng), 5));
	}

	return stars;
}

int main(int argv, char** args)
{
	Screen theScreen;

	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Vec2D centerPoint(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	std::vector<Star2D> myStars = CreateTenStars();
	cout << myStars.size() << endl;

	std::sort(myStars.begin(), myStars.end(), [](Star2D& aStar, Star2D& bStar)
	{
		return aStar.GetSize() > bStar.GetSize();
	});

	for(int i = 0; i < myStars.size(); i++)
	{
		theScreen.Draw(myStars[i], Color::Yellow());
	}

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