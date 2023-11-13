#ifndef SRC_SQUARE_H_
#define SRC_SQUARE_H_

#include "Vec2D.h"
#include "Line2D.h"

class Square2D
{
public:
    Square2D();
    Square2D(const int& side, const Vec2D& center);

	inline int GetSide() const { return mSide; }
	inline Vec2D GetCenter() const { return mCenter; }
	
private:
	int mSide;
	Vec2D mCenter;
};
#endif