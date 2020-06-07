#pragma once
#include "Colour.h"

class Material
{
public:
	Material(Colour colour, float ambient, float diffuse, float specular, float shininess)
		: colour_(colour)
		, ambient_(ambient)
		, diffuse_(diffuse)
		, specular_(specular)
		, shininess_(shininess)
	{
	}

	Material() //default
		: colour_(Colour(1,1,1))
		, ambient_(0.1f)
		, diffuse_(0.9f)
		, specular_(0.9f)
		, shininess_(200.0f)
	{
	}

	Colour colour() const { return colour_; }
	float ambient() const { return ambient_; }
	float diffuse() const { return diffuse_; }
	float specular() const { return specular_; }
	float shininess() const { return shininess_; }
	Colour& colour() { return colour_; }
	float& ambient() { return ambient_; }
	float& diffuse() { return diffuse_; }
	float& specular() { return specular_; }
	float& shininess() { return shininess_; }

	bool operator==(Material const& other);
	bool operator==(Material& other);
	bool operator!=(Material const& other);
	bool operator!=(Material& other);

private:							   
	Colour colour_;
	float ambient_;
	float diffuse_;
	float specular_;
	float shininess_;
};

bool operator==(const Material& first, const Material& other);
bool operator!=(const Material& first, const Material& other);

