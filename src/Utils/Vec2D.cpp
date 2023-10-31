/*
 * Vec2D.cpp
 *
 *  Created on: 30 oct 2023
 *      Author: Anto Martinez
 */

#include "Vec2D.h"
#include "Utils.h"

#include <cassert>
#include <cmath>

static const float EPSILON = 0.0001f;

std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec){
	std::cout << "X: " << vec.mX << ", Y: " << vec.mY << std::endl;
	return consoleOut;
}

Vec2D operator*(float scalar, const Vec2D& vec)
{
	return vec * scalar;
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

Vec2D Vec2D::operator*(float scale) const
{
	return Vec2D(mX*scale, mY*scale);
}

Vec2D Vec2D::operator/(float scale) const
{
	assert(fabsf(scale) > EPSILON);
	return Vec2D(mX/scale, mY/scale);
}

Vec2D& Vec2D::operator*=(float scale)
{
	*this = *this * scale;
	return *this;
}

Vec2D& Vec2D::operator/=(float scale)
{
	assert(fabsf(scale) > EPSILON);
	*this = *this / scale;
	return *this;
}

Vec2D Vec2D::operator+(const Vec2D& vec) const
{
	return Vec2D(mX + vec.mX, mY + vec.mY);
}

Vec2D& Vec2D::operator+=(const Vec2D& vec)
{
	return Vec2D(mX - vec.mX, mY - vec.mY);
}

Vec2D Vec2D::operator-(const Vec2D& vec) const
{
	*this = *this + vec;
	return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& vec)
{
	*this = *this - vec;
	return *this;
}

float Vec2D::Magnitude2() const
{
	return (mX * mX) + (mY * mY);
}

float Vec2D::Magnitude() const
{
	return sqrt(Magnitude2());
}
