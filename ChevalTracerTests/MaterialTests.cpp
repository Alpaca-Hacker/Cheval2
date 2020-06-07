#include "pch.h"

#include "../Cheval/src/Headers/Models/Material.h"

/*
 * Scenario: The default material
Given m ← material()
Then m.color = color(1, 1, 1)
And m.ambient = 0.1
And m.diffuse = 0.9
And m.specular = 0.9
And m.shininess = 200.0
 */

TEST(MaterialTests, DefaultMaterial)
{
	auto m = Material();

	EXPECT_EQ(m.colour(), Colour(1, 1, 1));
	EXPECT_EQ(m.ambient(), 0.1f);
	EXPECT_EQ(m.diffuse(), 0.9f);
	EXPECT_EQ(m.specular(), 0.9f);
	EXPECT_EQ(m.shininess(), 200.0f);
	
}
