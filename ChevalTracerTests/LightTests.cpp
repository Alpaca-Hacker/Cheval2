#include "pch.h"

#include "../Cheval/src/Headers/Models/Lights/Light.h"

TEST(LightTests, CreatePointLight)
{
	const auto intensity = Colour(1, 1, 1);
	const auto position = Point(0, 0, 0);
	
	auto light = point_light(position, intensity);

	EXPECT_EQ(light.position(), position);
	EXPECT_EQ(light.intensity(), intensity);
}
