#include "../Headers/DataStructures/Intersection.h"

#include <utility>

#include "../Headers/Helpers/Utils.h"

Intersection::Intersection(float time, ShapeConstPtr shape)
    : time_(time)
    , shape_(std::move(shape))
{}

Intersection Intersection::hit(std::vector<Intersection> &xs)
{
    std::sort(xs.begin(), xs.end());
	
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
