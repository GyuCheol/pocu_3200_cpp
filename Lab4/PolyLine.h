#pragma once

#include "Point.h"
#define MAX_COUNT 10

namespace lab4
{
	class PolyLine
	{
	public:

		PolyLine();
		PolyLine(const PolyLine& other);
		~PolyLine();

		bool AddPoint(float x, float y);
		bool AddPoint(const Point* point);
		bool RemovePoint(unsigned int i);
		bool TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const;

		const Point* operator[](unsigned int i) const;
	private:
		unsigned int mPointCount;
		const Point* mPointArray[10];

	};
}