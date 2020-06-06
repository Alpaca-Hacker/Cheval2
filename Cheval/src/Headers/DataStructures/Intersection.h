#pragma once
#include <algorithm>
#include <vector>

#include "../../Headers/Helpers/Types.h"

class Intersection
{
public:
    Intersection(float time, ShapeConstPtr s);

    float time() const { return time_; }
    ShapeConstPtr object() const { return shape_; }

    static Intersection hit(std::vector<Intersection> &xs);

    bool operator==(Intersection const& other) const;
    bool operator<(Intersection const& other) const;

private:
    float time_;
    ShapeConstPtr shape_;
};

inline bool Intersection::operator<(Intersection const& other) const
{
    return time_ < other.time_;
}

template<typename ...Args>
std::vector<Intersection> Intersections(Args const&... args)
{
    std::vector<Intersection> xs{ args... };
    std::sort(xs.begin(), xs.end());
    return xs;
}
