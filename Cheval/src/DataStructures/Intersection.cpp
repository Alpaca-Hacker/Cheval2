#include "../Headers/DataStructures/Intersection.h"

#include <utility>

#include "../Headers/Helpers/Utils.h"
#include "../Headers/Models/Shapes/Shape.h"

Intersection::Intersection(float time, ShapeConstPtr shape)
	: time_(time)
	, shape_(std::move(shape))
	, inside_(false)
{
}

void Intersection::prepare_computations(const Ray& ray)
{
    point_ = ray.position(time_);
    eyev_ = -ray.direction();
    normalv_ = shape_->normal_at(point_);
    inside_ = false;
    if (Tuple::dot(normalv_, eyev_) < 0)
    {
        inside_ = true;
        normalv_ = -normalv_;
    }
}

Intersection Intersection::hit(std::vector<Intersection> &xs)
{
    for (auto const& i : xs)
    {
        if (i.time() >= 0.f)
            return i;
    }
    return { 0.f, nullptr };
}

bool Intersection::operator==(Intersection const& other) const
{
    return Equals(time_ ,other.time_) && shape_ == other.shape_;
}
