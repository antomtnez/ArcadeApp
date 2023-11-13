#include "Screen.h"
#include "Vec2D.h"
#include "Line2D.h"
#include "Star2D.h"
#include "Square2D.h"
#include "ChessBoard.h"

#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>

Screen::Screen(): mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr) {}

Screen::~Screen()
{
    if(moptrWindow)
    {
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }

	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
{
    if(SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}

    mWidth = w;
    mHeight = h;

	moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

	if(moptrWindow)
	{
        mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
        
        SDL_PixelFormat* pixelFormat = mnoptrWindowSurface->format;

	    Color::InitColorFormat(pixelFormat);

        mClearColor = Color::Black();

        mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
        mBackBuffer.Clear(mClearColor);
	}

    return moptrWindow;
}

void Screen::SwapScreens()
{
    assert(moptrWindow);
    if(moptrWindow)
    {
        ClearScreen();

        SDL_BlitScaled(mBackBuffer.GetSuface(), nullptr, mnoptrWindowSurface, nullptr);

	    SDL_UpdateWindowSurface(moptrWindow);

        mBackBuffer.Clear(mClearColor); 

    }
}

//Draw Methods go here

void Screen::Draw(int x, int y, const Color& color)
{
    assert(moptrWindow);
    if(moptrWindow) mBackBuffer.SetPixel(color, x, y);
}
void Screen::Draw(const Vec2D& point, const Color& color)
{
    assert(moptrWindow);
    if(moptrWindow) mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
}

void Screen::Draw(const Line2D& line, const Color& color)
{
    assert(moptrWindow);
    if(moptrWindow)
    {
        int distanceX, distanceY;

        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        distanceX = x1 - x0;
        distanceY = y1 - y0;

        signed const char ix((distanceX > 0) - (distanceX < 0)); //evaluate to 1 or -1
        signed const char iy((distanceY > 0) - (distanceY < 0));

        distanceX = abs(distanceX) * 2;
        distanceY = abs(distanceY) * 2;

        Draw(x0, y0, color);

        if(distanceX >= distanceY)
        {
            //go along in the x
            int d = distanceY - distanceX/2;

            while(x0 != x1)
            {
                if(d >= 0) 
                {
                    d -= distanceX;
                    y0 += iy;
                }
                d += distanceY;
                x0 += ix;

                Draw(x0, y0, color);
            }
        }
        else
        {
            //go along in the y
            int d = distanceX - distanceY/2;

            while(y0 != y1)
            {
                if(d >= 0) 
                {
                    d -= distanceY;
                    x0 += ix;
                }
                d += distanceX;
                y0 += iy;

                Draw(x0, y0, color);
            }
        }
    }
}

void Screen::Draw(const Star2D& star, const Color& color)
{
    Line2D lineToDraw(star.GetStartLine());
    float angleBtwLines = 6.28 / star.GetPointsCount();

    for(int i=0; i < star.GetPointsCount(); i++)
    {
        Draw(lineToDraw, color);
        lineToDraw = {lineToDraw.GetP0(), lineToDraw.GetP1().RotationResult(angleBtwLines, lineToDraw.GetP0())};
        std::cout << star.GetPointsCount() << std::endl;
    }
}

void Screen::Draw(const Square2D& square, const Color& color)
{
    Line2D horizontalLine(Vec2D(0, 0), Vec2D(0, 0));

    for(int i = -square.GetSide()/2; i <= square.GetSide()/2; i++){
        horizontalLine = Line2D(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() + i)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() + i)));
        Draw(horizontalLine, color);
    }

/*
    Line2D topSide(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)));
    Line2D bottomSide(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)));
    Line2D leftSide(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)), Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)));
    Line2D rightSide(Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)));

    Draw(topSide, color);
    Draw(bottomSide, color);
    Draw(leftSide, color);
    Draw(rightSide, color);
    */
}

void Screen::DrawChessTable(const ChessBoard& chessboard, const Vec2D& startPoint)
{
    Square2D squareDrawed = Square2D(chessboard.GetSquareSize(), startPoint);
    for(int x = 1; x <= 8; x++)
    {
        for(int y = 1; y <= 8; y++)
        {
            squareDrawed = Square2D(chessboard.GetSquareSize(), Vec2D(startPoint.GetX() + (x * chessboard.GetSquareSize()), startPoint.GetY() + (y * chessboard.GetSquareSize())));
            if(x%2 != 0)
            {
                if(y%2 != 0)
                {
                    Draw(squareDrawed, Color::White());
                }
                else
                {
                    Draw(squareDrawed, Color::Black());
                }
            }
            else
            {
                if(y%2 != 0)
                {
                    Draw(squareDrawed, Color::Black());
                }
                else
                {
                    Draw(squareDrawed, Color::White());
                }
            }
        }
    }
}

void Screen::Draw(const Square2D& square, const Color& color, const int& angle)
{
    Line2D topSide(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)));
    Line2D bottomSide(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)));
    Line2D leftSide(Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)), Vec2D((square.GetCenter().GetX() - square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)));
    Line2D rightSide(Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() - square.GetSide()/2)), Vec2D((square.GetCenter().GetX() + square.GetSide()/2), (square.GetCenter().GetY() + square.GetSide()/2)));

    topSide = { topSide.GetP0().RotationResult(angle, square.GetCenter()), topSide.GetP1().RotationResult(angle, square.GetCenter()) };
    bottomSide = { bottomSide.GetP0().RotationResult(angle, square.GetCenter()), bottomSide.GetP1().RotationResult(angle, square.GetCenter()) };
    leftSide = { leftSide.GetP0().RotationResult(angle, square.GetCenter()), leftSide.GetP1().RotationResult(angle, square.GetCenter()) };
    rightSide = { rightSide.GetP0().RotationResult(angle, square.GetCenter()), rightSide.GetP1().RotationResult(angle, square.GetCenter()) };

    Draw(topSide, color);
    Draw(bottomSide, color);
    Draw(leftSide, color);
    Draw(rightSide, color);
}

void Screen::ClearScreen()
{
    assert(moptrWindow);
    if(moptrWindow) SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
}