#include "pch.h"

#include "../Cheval/src/Headers/Models/Canvas.h"

TEST(CanvasTest, CanvasWritesCorrectly)
{
	const auto image_height = 256;
	const auto image_width = 256;
	auto c = Canvas(image_height, image_width);

	for (int j = image_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < image_width; ++i)
		{
			auto r = static_cast<float>(i) / (image_width - 1.0f);
			auto g = static_cast<float>(j) / (image_height - 1.0f);
			auto b = 0.25f;

			c.write_pixel(i, j, Colour(r, g, b));
		}
	}

	EXPECT_EQ(c.write_file("d:/TestImage.jpg"), 1);
}
