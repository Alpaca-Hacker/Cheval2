#include "../../Headers/Models/Shapes/Sphere.h"

#include "../../Headers/DataStructures/Tuple.h"
#include "../../Headers/Helpers/Utils.h"


void Sphere::intersect(Ray const& rayO, std::vector<Intersection>& xs) const
{
	const auto ray = Ray::transform(rayO, transform_inverse());

	const auto s2r = ray.origin() - Point(0, 0, 0);

	const auto a = Tuple::dot(ray.direction(), ray.direction());
	const auto b = 2 * Tuple::dot(ray.direction(), s2r);
	const auto c = Tuple::dot(s2r, s2r) - 1;

	float t1, t2;
	if (!SolveQuadratic(a, b, c, t1, t2)) {
		return;
	}
	
	xs.emplace_back(t1, shared_from_this());
	xs.emplace_back(t2, shared_from_this());
}

Tuple Sphere::normal_at(const Tuple& point) const
{
	const auto object_point = transform_inverse() * point;
	const auto object_normal = object_point - Point(0, 0, 0);
	auto world_normal = transform_inverse().transpose() * object_normal;
	world_normal.W() = 0;
	return Tuple::normalize(world_normal);
}