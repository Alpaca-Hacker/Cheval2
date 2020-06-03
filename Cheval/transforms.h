#pragma once

#include "Matrix.h"


namespace matrix
{
    Matrix translation(float x, float y, float z);
    Matrix scaling(float x, float y, float z);
    Matrix rotation_x(float radians);
    Matrix rotation_y(float radians);
    Matrix rotation_z(float radians);
    Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);
   // Matrix View(Tuple const& from, Tuple const& to, Tuple const& up);
}

