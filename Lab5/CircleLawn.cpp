#include "CircleLawn.h"

namespace lab5
{

	CircleLawn::CircleLawn(unsigned int radius)
		: mRadius(radius)
	{

	}

	unsigned int CircleLawn::GetArea() const
	{
		return (unsigned int) std::round(mRadius * mRadius * PI);
	}

}