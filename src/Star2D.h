#ifndef SRC_STAR_H_
#define SRC_STAR_H_

#include "Vec2D.h"
#include "Line2D.h"
#include <vector>

class Star2D
{
public:
	Star2D();
	Star2D(const Vec2D& centerPoint, int size, int count);

	inline void SetCenter(const Vec2D& center) { mPoints[0] = center; }

	inline int GetPointsCount() const { return mPointsCount; }
	inline Vec2D GetCenter() const { return mPoints[0]; }
	inline std::vector<Vec2D> GetPoints() const { return mPoints; }
	inline int GetSize() const { return mSize; }

	static Star2D RandomSizeStar(const Vec2D& centerPoint, int count) ;
	
private:
	int mSize;
	int mPointsCount;
	std::vector<Vec2D> mPoints;
};
#endif