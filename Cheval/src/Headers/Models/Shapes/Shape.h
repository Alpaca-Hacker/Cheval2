#pragma once
#include <memory>
#include <vector>

#include "../../DataStructures/Intersection.h"
#include "../Ray.h"


class Shape : public std::enable_shared_from_this<Shape>
{
public:
	Shape();
	virtual void intersect(Ray const& ray, std::vector<Intersection>& xs) const = 0;
};

