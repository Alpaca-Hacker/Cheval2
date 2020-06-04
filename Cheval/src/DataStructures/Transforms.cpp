#include <cmath>
#include "../Headers/DataStructures/Transforms.h"


Matrix matrix::translation(float x, float y, float z)
{
    auto transform = Matrix::identity();
    transform(0, 3) = x;
    transform(1, 3) = y;
    transform(2, 3) = z;
    return transform;
}

Matrix matrix::scaling(float x, float y, float z)
{
    auto transform = Matrix::identity();
    transform(0, 0) = x;
    transform(1, 1) = y;
    transform(2, 2) = z;
    return transform;
}

Matrix matrix::rotation_x(float radians)
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

Matrix matrix::rotation_y(float radians)
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

Matrix matrix::rotation_z(float radians)
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

Matrix matrix::shearing(float xy, float xz, float yx, float yz, float zx, float zy)
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


