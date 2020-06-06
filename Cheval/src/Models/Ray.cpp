
#include "../Headers/Models/Ray.h"


Tuple Ray::position(float time) const
{
	return origin_ + direction_ * time;
}

Ray Ray::transform(const Ray& ray, const Matrix& transform)
{
	return { ray * transform };
	//{ ray.origin() * transform, ray.direction() * transform };
}

Ray operator*(Ray const& ray, const Matrix& rhs)
{
	return { ray.origin() * rhs, ray.direction() * rhs };
}

