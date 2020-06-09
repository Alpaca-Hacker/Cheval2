#pragma once
#include "../Models/Material.h"
#include "../Models/Lights/Light.h"

class Integrator
{
public:
	static Colour lighting(const Material& material, const Light& light, const Tuple& position, const Tuple& eyev, const Tuple& normalv, bool inShadow = false);
};

