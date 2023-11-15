#include "Triangle.h"
#include "Vec2D.h"
#include "Utils.h"

#include <cmath>

Triangle::Triangle(): Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero) {}
Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2)
{
    mPoints.push_back(p0);
    mPoints.push_back(p1);
    mPoints.push_back(p2);
}

Vec2D Triangle::GetCenterPoint() const 
{
    return Vec2D((mPoints[0].GetX() + mPoints[1].GetX() + mPoints[2].GetX()) / 3.0f, (mPoints[0].GetY() + mPoints[1].GetY() + mPoints[2].GetY()) / 3.0f);
}

void Triangle::MoveTo(const Vec2D& position)
{
    Vec2D centerPoint = GetCenterPoint();

    Vec2D distanceP0ToCenter = Vec2D(GetP0().GetX() - centerPoint.GetX(), GetP0().GetY() - centerPoint.GetY()); 
    Vec2D distanceP1ToCenter = Vec2D(GetP1().GetX() - centerPoint.GetX(), GetP1().GetY() - centerPoint.GetY());
    Vec2D distanceP2ToCenter = Vec2D(GetP2().GetX() - centerPoint.GetX(), GetP2().GetY() - centerPoint.GetY());

    SetP0(Vec2D(distanceP0ToCenter.GetX() + position.GetX(), distanceP0ToCenter.GetY() + position.GetY()));
    SetP1(Vec2D(distanceP1ToCenter.GetX() + position.GetX(), distanceP1ToCenter.GetY() + position.GetY()));
    SetP2(Vec2D(distanceP2ToCenter.GetX() + position.GetX(), distanceP2ToCenter.GetY() + position.GetY()));
}

float Triangle::Area() const 
{
    return Area(GetP0(), GetP1(), GetP2());
}

float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const 
{
    return fabsf((p0.GetX() * (p1.GetY() - p2.GetY()) + p1.GetX() * (p2.GetY() - p0.GetY()) + p2.GetX() * (p0.GetY() - p1.GetY())) / 2.0f);
}

bool Triangle::ContainsPoint(const Vec2D& p) const 
{
    float thisArea = Area();

    float a1 = Area(p, GetP1(), GetP2());
    float a2 = Area(GetP0(), p, GetP2());
    float a3 = Area(GetP0(), GetP1(), p);

    return IsEqual(thisArea, a1 + a2 + a3);
}