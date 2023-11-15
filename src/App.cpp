#include "App.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>

#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Star2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"

static App& Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
    mnoptrWindow = mScreen.Init(width, height, mag);
    return mnoptrWindow != nullptr;
}

void App::Run()
{
    if(mnoptrWindow)
    {
        Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110) };
        AARectangle rectangle = { Vec2D(mScreen.Width()/2 - 50, mScreen.Height()/2 -25), 50, 100 };
        Circle circle = { Vec2D(mScreen.Width()/2 + 50, mScreen.Height()/2 + 50), 50 };

        mScreen.Draw(triangle, Color::Red(), true, Color::White());
        mScreen.Draw(rectangle, Color::Blue(), true, Color::Blue());
        mScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));

        mScreen.SwapScreens();

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
    }
}