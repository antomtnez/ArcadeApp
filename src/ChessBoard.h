#ifndef SRC_CHESSBOARD_H_
#define SRC_CHESSBOARD_H_

#include "Vec2D.h"

class ChessBoard
{
public:
    ChessBoard(): mSquareSize(1) {} ;
    ChessBoard(const int& squareSize);

    inline int GetSquareSize() const { return mSquareSize; }
    inline Vec2D GetBoardPosition(int x, int y) const { return mBoardSquare[x][y]; }

private:
    Vec2D mBoardSquare[8][8];
    int mSquareSize;
};

#endif