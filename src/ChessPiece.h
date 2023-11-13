#ifndef SRC_CHESSPIECE_H_
#define SRC_CHESSPIECE_H_

#include "Vec2D.h"

class Piece
{
public:


private:
    Vec2D boardPosition;
    int drawSchema[24][24];
};

class Pawn : public Piece
{

};

class Bishop : public Piece
{

};

class Knight : public Piece
{

};

class Rook : public Piece
{

};

class Queen : public Piece
{

};

class King : public Piece
{

};

#endif