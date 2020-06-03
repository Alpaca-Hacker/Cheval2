#include "Ray.h"

Tuple Ray::position(float time) const
{
	return origin_ + direction_ * time;
}
