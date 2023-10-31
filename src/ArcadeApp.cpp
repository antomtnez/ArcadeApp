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

class DinamicIntArray
{
public:
	DynamicIntArray():moptrData(nullptr), mSize(0), mCapacity(0){}
	//DynamicIntArray(const DynamicIntArray& otherArray);
	//should clean up the memory
	~DynamicIntArray();

	inline size_t Size() const { return mSize; }
	inline size_t Capacity() const { return mCapacity; }

	//Allocates the dynamic array
	bool Init(size_t capacity = INITIAL_CAPACITY);
	bool Reserve(size_t capacity);
	bool Resize()
};

int main()
{
	return 0;
}
