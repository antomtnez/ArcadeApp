#include "Shape.h"

void Shape::MoveBy(const Vec2D& deltaOffset)
{
    for(Vec2D& vecPoint : mPoints)
    {
        vecPoint = vecPoint + deltaOffset;
    }
}