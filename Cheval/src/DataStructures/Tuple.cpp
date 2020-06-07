
#include "../Headers/DataStructures/Tuple.h"
#include "../Headers/Helpers/Utils.h"

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

bool Tuple::is_point() const
{
	return Equals(w_, 1.0f);
}

bool Tuple::is_vector() const
{
	return Equals(w_, 0.0f);
}

Tuple Tuple::normalize(const Tuple& v)
{
	const auto mag = v.magnitude();
	return Vector(v.X() / mag, v.Y() / mag, v.Z() / mag);
}

float Tuple::dot(const Tuple& a, const Tuple& b)
{
	return a.X() * b.X() +
		a.Y() * b.Y() +
		a.Z() * b.Z();
}

Tuple Tuple::cross(const Tuple& a, const Tuple& b)
{
	return Vector(a.Y() * b.Z() - a.Z() * b.Y(),
				  a.Z() * b.X() - a.X() * b.Z(),
				  a.X() * b.Y() - a.Y() * b.X());
}

bool operator==(const Tuple& first, const Tuple& other)
{
	return Equals(first.X(), other.X())
		&& Equals(first.Y(), other.Y())
		&& Equals(first.Z(), other.Z())
		&& Equals(first.W(), other.W());
}

bool operator!=(const Tuple& first, const Tuple& other)
{
	return !(Equals(first.X(), other.X())
		&& Equals(first.Y(), other.Y())
		&& Equals(first.Z(), other.Z())
		&& Equals(first.W(), other.W()));
}


bool Tuple::operator==(const Tuple& other)
{
	return Equals(X(), other.X())
		&& Equals(Y(), other.Y())
		&& Equals(Z(), other.Z())
		&& Equals(W(), other.W());
}

bool Tuple::operator!=(const Tuple& other)
{
	return !this->operator==(other);
}

bool Tuple::operator==(Tuple& other)
{
	return Equals(X(), other.X())
		&& Equals(Y(), other.Y())
		&& Equals(Z(), other.Z())
		&& Equals(W(), other.W());
}

bool Tuple::operator!=(Tuple& other)
{
	return !this->operator==(other);
}

Tuple Tuple::reflect(const Tuple& in, const Tuple& normal)
{
	return { in - normal * 2 * dot(in, normal) };
}

float Tuple::magnitude() const
{
	return std::sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
}

