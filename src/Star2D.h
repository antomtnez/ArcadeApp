#ifndef SRC_STAR_H_
#define SRC_STAR_H_

#include "Vec2D.h"
#include "Line2D.h"

class Star2D
{
public:
	Star2D();
	Star2D(const Line2D& firstLine, int count);

	inline Line2D GetStartLine() const { return startLine; }
	inline int GetPointsCount() const { return pointsCount; }
	
private:
	Line2D startLine;
	int pointsCount;
};
#endif