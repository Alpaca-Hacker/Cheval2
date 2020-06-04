#pragma once
#include "../DataStructures/Tuple.h"

class Ray
{
public:
	Ray(Tuple origin, Tuple direction)
		: origin_(origin)
		, direction_(direction)
	{
	}

	Tuple position(float time) const;

	Tuple origin() const
	{
		return origin_;
	}

	Tuple direction() const
	{
		return direction_;
	}

private:
	Tuple origin_;
	Tuple direction_;
};

