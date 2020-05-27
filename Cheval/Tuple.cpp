#include "Tuple.h"

Tuple::Tuple()
	: x_( 0.0f),
	y_(0.0f),
	z_(0.0f),
	w_(0.0f)
{
}

Tuple::Tuple(float x, float y, float z, float w)
	: x_(x),
	y_(y),
	z_(z),
	w_(w)
{
}

