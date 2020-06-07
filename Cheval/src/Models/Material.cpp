#include "../Headers/Models/Material.h"

bool Material::operator==(Material const& other)
{
	return colour_ == other.colour_ &&
			ambient_ == other.ambient_ &&
			diffuse_ == other.diffuse_ &&
			specular_ == other.specular_ &&
			shininess_ == other.shininess_;
}

bool Material::operator==(Material& other)
{
	return colour_ == other.colour_ &&
		ambient_ == other.ambient_ &&
		diffuse_ == other.diffuse_ &&
		specular_ == other.specular_ &&
		shininess_ == other.shininess_;
}

bool Material::operator!=(Material const& other)
{
	return !this->operator==(other);
}

bool Material::operator!=(Material& other)
{
	return !this->operator==(other);
}

bool operator==(const Material& first, const Material& other)
{
	return
		first.colour() == other.colour() &&
		first.ambient() == other.ambient() &&
		first.diffuse ()== other.diffuse() &&
		first.specular()== other.specular() &&
		first.shininess() == other.shininess();
}

bool operator!=(const Material& first, const Material& other)
{
	return
		first.colour() != other.colour() ||
		first.ambient() != other.ambient() ||
		first.diffuse() != other.diffuse() ||
		first.specular() != other.specular() ||
		first.shininess() != other.shininess();
}

