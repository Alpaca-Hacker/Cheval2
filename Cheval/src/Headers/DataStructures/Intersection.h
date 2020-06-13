#pragma once
#include <algorithm>
#include <vector>


#include "Tuple.h"
#include "../../Headers/Helpers/Types.h"
#include "../Models/Ray.h"

class Intersection
{
public:
    Intersection(float time, ShapeConstPtr s);

    float time() const { return time_; }
    ShapeConstPtr object() const { return shape_; }
    Tuple point() const { return point_; }
    Tuple eyeV() const{ return eyev_; }
    Tuple normalV() const{ return normalv_; }
    bool inside() const { return inside_; }

	void prepare_computations(const Ray& ray);
    static Intersection hit(std::vector<Intersection> &xs);

    bool operator==(Intersection const& other) const;
    bool operator<(Intersection const& other) const;

private:
    float time_;
    ShapeConstPtr shape_;
    Tuple point_;
    Tuple eyev_;
    Tuple normalv_;
    bool inside_;
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
