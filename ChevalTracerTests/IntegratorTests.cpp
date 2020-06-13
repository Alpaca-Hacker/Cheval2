#include "pch.h"



#include "../Cheval/src/Headers/Helpers/Utils.h"
#include "../Cheval/src/Headers/Integrators/Integrator.h"
#include "../Cheval/src/Headers/Models/Material.h"
#include "../Cheval/src/Headers/Models/Lights/Light.h"

/*
 * Background:
Given m ← material()
And position ← point(0, 0, 0)
 */
auto m = Material();
auto position = Point(0, 0, 0);

//Scenario: Lighting with the eye between the light and the surface
//Given eyev ← vector(0, 0, -1)
//And normalv ← vector(0, 0, -1)
//And light ← point_light(point(0, 0, -10), color(1, 1, 1))
//When result ← lighting(m, light, position, eyev, normalv)
//Then result = color(1.9, 1.9, 1.9)
//
TEST(IntegratorTests, BetweenLightAndSurface)
{
	const auto eyev = Vector(0, 0, -1);
	const auto normalv = Vector(0, 0, -1);
	const auto light = Point_Light(Point(0, 0, -10), Colour(1, 1, 1));

    auto result = Integrator::lighting(m, light, position, eyev, normalv);

    EXPECT_EQ(result, Colour(1.9, 1.9, 1.9));
}

//Scenario: Lighting with the eye between light and surface, eye offset 45°
//Given eyev ← vector(0, √2 / 2, -√2 / 2)
//And normalv ← vector(0, 0, -1)
//And light ← point_light(point(0, 0, -10), color(1, 1, 1))
//When result ← lighting(m, light, position, eyev, normalv)
//Then result = color(1.0, 1.0, 1.0)

TEST(IntegratorTests, BetweenLightAndSurfaceoffset45)
{
	const auto eyev = Vector(0, SQRT2DIV2, -SQRT2DIV2);
	const auto normalv = Vector(0, 0, -1);
	const auto light = Point_Light(Point(0, 0, -10), Colour(1, 1, 1));

    auto result = Integrator::lighting(m, light, position, eyev, normalv);

    EXPECT_EQ(result, Colour(1.0, 1.0, 1.0));
}

//Scenario: Lighting with eye opposite surface, light offset 45°
//Given eyev ← vector(0, 0, -1)
//And normalv ← vector(0, 0, -1)
//And light ← point_light(point(0, 10, -10), color(1, 1, 1))
//When result ← lighting(m, light, position, eyev, normalv)
//Then result = color(0.7364, 0.7364, 0.7364)

TEST(IntegratorTests, OppositeSurfaceLightOffset45)
{
	const auto eyev = Vector(0, 0, -1);
	const auto normalv = Vector(0, 0, -1);
	const auto light = Point_Light(Point(0, 10, -10), Colour(1, 1, 1));

    auto result = Integrator::lighting(m, light, position, eyev, normalv);

    EXPECT_EQ(result, Colour(0.7364, 0.7364, 0.7364));
}

/*
 * Scenario: Lighting with eye in the path of the reflection vector
Given eyev ← vector(0, -√2/2, -√2/2)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 10, -10), color(1, 1, 1))
When result ← lighting(m, light, position, eyev, normalv)
Then result = color(1.6364, 1.6364, 1.6364)
 */

TEST(IntegratorTests, InPathOf45Reflection)
{
	const auto eyev = Vector(0, -SQRT2DIV2, -SQRT2DIV2);
	const auto normalv = Vector(0, 0, -1);
	const auto light = Point_Light(Point(0, 10, -10), Colour(1, 1, 1));

    auto result = Integrator::lighting(m, light, position, eyev, normalv);

    EXPECT_EQ(result, Colour(1.6364, 1.6364, 1.6364));
}

/*
 * Scenario: Lighting with the light behind the surface
Given eyev ← vector(0, 0, -1)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 0, 10), color(1, 1, 1))
When result ← lighting(m, light, position, eyev, normalv)
Then result = color(0.1, 0.1, 0.1)
 */

TEST(IntegratorTests, LightBehindSurface)
{
	const auto eyev = Vector(0, 0, -1);
	const auto normalv = Vector(0, 0, -1);
	const auto light = Point_Light(Point(0, 0, 10), Colour(1, 1, 1));

    auto result = Integrator::lighting(m, light, position, eyev, normalv);

    EXPECT_EQ(result, Colour(0.1, 0.1, 0.1));
}