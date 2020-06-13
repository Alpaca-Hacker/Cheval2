#include "pch.h"

#include "../Cheval/src/Headers/Helpers/Utils.h"
#include "../Cheval/src/Headers/Models/Camera.h"

/*
 * Scenario: Constructing a camera
Given hsize ← 160
And vsize ← 120
And field_of_view ← π/2
When c ← camera(hsize, vsize, field_of_view)
Then c.hsize = 160
And c.vsize = 120
And c.field_of_view = π/2
And c.transform = identity_matrix
 */

TEST(CameraTests, DefaultCamera)
{
	const auto hsize = 160;
	const auto vsize = 120;
	const auto fov = PIDIV2;

	auto c = Camera(hsize, vsize, fov);

	EXPECT_EQ(c.h_size(), 160);
	EXPECT_EQ(c.v_size(), 120);
	EXPECT_EQ(c.fov(), PIDIV2);

	EXPECT_EQ(c.transform(), Matrix::identity());
}

/*
 * Scenario: The pixel size for a horizontal canvas
Given c ← camera(200, 125, π/2)
Then c.pixel_size = 0.01
*/
TEST(CameraTests, PixalSizeH)
{
	auto c = Camera(200, 125, PIDIV2);
	EXPECT_FLOAT_EQ(c.pixel_size(), 0.01f);
}

/*
Scenario: The pixel size for a vertical canvas
Given c ← camera(125, 200, π/2)
Then c.pixel_size = 0.01
 */

TEST(CameraTests, PixalSizeV)
{
	auto c = Camera(125, 200, PIDIV2);
	EXPECT_FLOAT_EQ(c.pixel_size(), 0.01f);
}
