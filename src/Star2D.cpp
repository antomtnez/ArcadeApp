#include "Star2D.h"
#include "Vec2D.h"
#include <vector>
#include <random>

Star2D::Star2D(): Star2D(Vec2D(0, 0), 1, 3) {}

Star2D::Star2D(const Vec2D& centerPoint, int size, int count): mSize(size), mPointsCount(count) 
{
    mPoints.reserve(GetPointsCount());
    mPoints.push_back(centerPoint);
    mPoints.push_back(Vec2D(centerPoint.GetX(), centerPoint.GetY() - mSize));

    float angleBtwLines = 6.28 / GetPointsCount();

    for(int i=1; i < GetPointsCount(); i++)
    {
        mPoints.push_back(mPoints[1].RotationResult(angleBtwLines * i, centerPoint));
    }
}

Star2D Star2D::RandomSizeStar(const Vec2D& centerPoint, int count)
{
    std::random_device r;
    std::default_random_engine randEng(r());
    std::uniform_int_distribution<int> uniform_dist(5, 30);

    int randomSize = uniform_dist(randEng);

    return Star2D(centerPoint, randomSize, count);
}