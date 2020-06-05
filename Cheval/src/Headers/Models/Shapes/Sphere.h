#pragma once

#include "Shape.h"
#include "../Ray.h"


class Sphere : public Shape
{
public:
	void intersect(Ray const& ray, std::vector<Intersection>& xs) const override;
	
};

