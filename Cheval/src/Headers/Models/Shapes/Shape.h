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
	virtual Tuple normal_at(const Tuple& point) const = 0;

	Matrix transform() const
	{
		return transform_;
	}
	
	void setTransform(Matrix &matrix)
	{
		transform_ = matrix;
		transform_inverse_ = matrix.inverse();
	}

	Matrix transform_inverse() const
	{
		return transform_inverse_;
	}
	
private:
	Matrix transform_ = Matrix::identity();
	Matrix transform_inverse_ = transform_.inverse();
};


