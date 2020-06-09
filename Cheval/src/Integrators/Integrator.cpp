#include "../Headers/Integrators/Integrator.h"
#include  <cmath>

Colour Integrator::lighting(const Material& material, const Light& light, const Tuple& position, const Tuple& eyev,
	const Tuple& normalv, bool inShadow)
{
	const auto effective_colour = material.colour() * light.intensity();
	const auto lightv = Tuple::normalize(light.position() - position);

	const auto ambient = effective_colour * material.ambient();

	/*
	 * light_dot_normal represents the cosine of the angle between the
	 * light vector and the normal vector. A negative number means the
	 * light is on the other side of the surface.
	 */

	const auto light_dot_normal = Tuple::dot(lightv, normalv);
	auto diffuse = Colour::Black();
	auto specular = Colour::Black();

	if (light_dot_normal >= 0)
	{
		diffuse = effective_colour * material.diffuse() * light_dot_normal;
		/*
		 * reflect_dot_eye represents the cosine of the angle between the
		 * reflection vector and the eye vector. A negative number means the
		 * light reflects away from the eye.
		 */
		const auto reflectv = Tuple::reflect(-lightv, normalv);
		const auto reflect_dot_eye = Tuple::dot(reflectv, eyev);

		if (reflect_dot_eye > 0)
		{
			auto const factor = std::powf(reflect_dot_eye, material.shininess());
			specular = light.intensity() * material.specular() * factor;
		}
	}

	auto returnValue = ambient;
	if (!inShadow)
	{
		returnValue = returnValue + diffuse + specular;
	}

	return returnValue;
	
}
