//============================================================================
// Name        : ArcadeApp.cpp
// Author      : antomtnezdev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Vec2D.h"

using namespace std;

int main()
{
	Vec2D aVec(3, -7);

	Vec2D resultVec = aVec * 3;

	cout << aVec << endl;

	cout << -aVec << endl;

	cout << aVec*3 << endl;

	cout << resultVec << endl;

	return 0;
}
