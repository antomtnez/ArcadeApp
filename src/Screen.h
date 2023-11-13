#ifndef SRC_SCREEN_H
#define SRC_SCREEN_H

#include <stdint.h>
#include "ScreenBuffer.h"
#include "Color.h"

class Vec2D;
class Line2D;
class Star2D;
class Square2D;
class ChessBoard;
struct SDL_Window;
struct SDL_Surface;

class Screen
{
public:
    Screen();
    ~Screen();

    SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapScreens();

    inline void SetClearColor(const Color& clearColor) { mClearColor = clearColor; }
    inline uint32_t Width() const { return mWidth; }
    inline uint32_t Height() const { return mHeight; }

    //Draw Methods go here

    void Draw(int x, int y, const Color& color);
    void Draw(const Vec2D& point, const Color& color);
    void Draw(const Line2D& line, const Color& color);
    void Draw(const Star2D& star, const Color& color);
    void Draw(const Square2D& square, const Color& color);
    void Draw(const Square2D& square, const Color& color, const int& angleRotation);

    void DrawChessTable(const ChessBoard& chessboard, const Vec2D& startPoint);

private:

    Screen(const Screen& screen);
    Screen& operator=(const Screen& screen);

    void ClearScreen();

    uint32_t mWidth, mHeight;

    Color mClearColor;
    ScreenBuffer mBackBuffer;

    SDL_Window* moptrWindow;
    SDL_Surface* mnoptrWindowSurface;
};

#endif