#pragma once

#include "Shape.h"
#include "../Ray.h"


class Sphere : public Shape
{
public:
	void intersect(Ray const& ray, std::vector<Intersection>& xs) const override;
	Tuple normal_at(const Tuple& point) const override;

};

