#pragma once
#include "../DataStructures/Tuple.h"
#include "../DataStructures/Matrix.h"

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

	static Ray transform(const Ray& ray, const Matrix& transform);
	

private:
	Tuple origin_;
	Tuple direction_;
};

Ray operator*(Ray const& ray, const Matrix& rhs);

