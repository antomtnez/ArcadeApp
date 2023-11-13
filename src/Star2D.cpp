#include "Star2D.h"
#include "Vec2D.h"

Star2D::Star2D(): startLine(Line2D(Vec2D(0, 0),Vec2D(0, 1))), pointsCount(3) {}

Star2D::Star2D(const Line2D& firstLine, int count): startLine(firstLine), pointsCount(count) {}