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

const Vec2D Vec2D::Zero;
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
	return Dot(*this);
}

float Vec2D::Magnitude() const
{
	return sqrt(Magnitude2());
}

Vec2D Vec2D::GetUnitVector() const
{
	float mag = Magnitude();
	if(mag > EPSILON){
		return *this / mag;
	}

	return Vec2D::Zero;
}

Vec2D& Vec2D::Normalize()
{
	float mag = Magnitude();
	if(mag > EPSILON){
		*this /= mag;
	}

	return *this;
}

float Vec2D::Distance(const Vec2D& vec) const
{
	return (vec - *this).Magnitude();
}

float Vec2D::Dot(const Vec2D& vec) const
{
	return (mX * vec.mX) + (mY * vec.mY);
}

Vec2D Vec2D::ProjectOnto(const Vec2D& vec) const
{
	Vec2D unitVec = vec.GetUnitVector();

	float dot = Dot(unitVec);

	return unitVec * dot;
}

float Vec2D::AngleBetween(const Vec2D& vec) const
{
	return acosf(GetUnitVector().Dot(vec.GetUnitVector()));
}

Vec2D Vec2D::Reflect(const Vec2D& normal) const
{
	return *this - 2 * (ProjectOnto(normal));
}

void Vec2D::Rotate(float angle, const Vec2D& aroundPoint)
{
	float cos = cosf(angle);
	float sin = sinf(angle);

	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRotation = thisVec.mX * cos - thisVec.mY * sin;
	float yRotation = thisVec.mX * sin + thisVec.mY * cos;

	Vec2D rotation = Vec2D(xRotation, yRotation);

	*this = rotation + aroundPoint;
}

Vec2D Vec2D::RotationResult(float angle, const Vec2D& aroundPoint) const
{
	float cos = cosf(angle);
	float sin = sinf(angle);

	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRotation = thisVec.mX * cos - thisVec.mY * sin;
	float yRotation = thisVec.mX * sin + thisVec.mY * cos;

	Vec2D rotation = Vec2D(xRotation, yRotation);

	return rotation + aroundPoint;
}
