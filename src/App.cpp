#include "App.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>

#include "Color.h"
#include "Screen.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"

App& App::Singleton()
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
        AARectangle rectangle = { Vec2D(mScreen.Width()/2 - 50, mScreen.Height()/2 - 25), 100, 50 };
        Circle circle = { Vec2D(mScreen.Width()/2 + 50, mScreen.Height()/2 + 50), 25 };

        SDL_Event sdlEvent;
        bool running = true;

        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;

        uint32_t dt = 10;
        uint32_t accumulator = 0;

        while(running)
        {
            currentTick = SDL_GetTicks();
            uint32_t frameTime = currentTick - lastTick;

            if(frameTime > 300) frameTime = 300;

            lastTick = currentTick;
            
            accumulator += frameTime;

            //INPUT
            while(SDL_PollEvent(&sdlEvent))
            {
                switch(sdlEvent.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;
                }
            }

            //UPDATE
            while(accumulator >= dt)
            {
                //Update current scene by dt
                std::cout << "Delta time step" << dt << std::endl; 
                accumulator -= dt;
            }

            //RENDER
            mScreen.Draw(triangle, Color::Red(), true, Color::White());
            mScreen.Draw(rectangle, Color::Blue(), true, Color::Blue());
            mScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));

            mScreen.SwapScreens();
        }
    }
}