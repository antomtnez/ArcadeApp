#include "Square2D.h"
#include "Vec2D.h"

Square2D::Square2D(): mSide(1), mCenter(Vec2D(0, 0)) {}

Square2D::Square2D(const int& side, const Vec2D& center): mSide(side), mCenter(center) {}