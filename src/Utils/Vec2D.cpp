/*
 * Vec2D.cpp
 *
 *  Created on: 30 oct 2023
 *      Author: Anto Martinez
 */

#include "Vec2D.h"
#include "Utils.h"

std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec){
	std::cout << "X: " << vec.mX << ", Y: " << vec.mY << std::endl;
	return consoleOut;
}

bool Vec2D::operator==(const Vec2D& vec2) const
{
	return IsEqual(mX, vec2.mX) && IsEqual(mY, vec2.mY);
}

bool Vec2D::operator!=(const Vec2D& vec2) const
{
	return !(*this == vec2);
}

Vec2D Vec2D::operator-() const
{
	return Vec2D(-mX, -mY);
}
