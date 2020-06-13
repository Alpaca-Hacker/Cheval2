#include <cmath>
#include "../Headers/DataStructures/Transforms.h"


Matrix transforms::translation(float x, float y, float z)
{
    auto transform = Matrix::identity();
    transform(0, 3) = x;
    transform(1, 3) = y;
    transform(2, 3) = z;
    return transform;
}

Matrix transforms::scaling(float x, float y, float z)
{
    auto transform = Matrix::identity();
    transform(0, 0) = x;
    transform(1, 1) = y;
    transform(2, 2) = z;
    return transform;
}

Matrix transforms::rotation_x(float radians)
{
    float const c = std::cos(radians);
    float const s = std::sin(radians);
    auto transform = Matrix::identity();
    transform(1, 1) = c;
    transform(1, 2) = -s;
    transform(2, 1) = s;
    transform(2, 2) = c;
    return transform;
	
}

Matrix transforms::rotation_y(float radians)
{
    float const c = std::cos(radians);
    float const s = std::sin(radians);
    auto transform = Matrix::identity();
    transform(0, 0) = c;
    transform(0, 2) = s;
    transform(2, 0) = -s;
    transform(2, 2) = c;
    return transform;
}

Matrix transforms::rotation_z(float radians)
{
    float const c = std::cos(radians);
    float const s = std::sin(radians);
    auto transform = Matrix::identity();
    transform(0, 0) = c;
    transform(0, 1) = -s;
    transform(1, 0) = s;
    transform(1, 1) = c;
    return transform;
}

Matrix transforms::shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    auto transform = Matrix::identity();
    transform(0, 1) = xy;
    transform(0, 2) = xz;
    transform(1, 0) = yx;
    transform(1, 2) = yz;
    transform(2, 0) = zx;
    transform(2, 1) = zy;
    return transform;
}

Matrix transforms::View(Tuple const& from, Tuple const& to, Tuple const& up)
{
    auto forward = Tuple::normalize(to - from);
    const auto upn = Tuple::normalize(up);
    auto left = Tuple::cross(forward, upn);
    auto true_up = Tuple::cross(left, forward);
    const auto orientation = Matrix(4, std::vector<float>{
        left.X(),    left.Y(),    left.Z(), 0,
     true_up.X(), true_up.Y(), true_up.Z(), 0,
    -forward.X(),-forward.Y(),-forward.Z(), 0,
               0,           0,           0, 1});
	
    return orientation * translation(-from.X(), -from.Y(), -from.Z());
}


