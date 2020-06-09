#include <iostream>

#include "../Cheval/src/Headers/Models/Canvas.h"
#include "../Cheval/src/Headers/Models/Shapes/Sphere.h"
#include "Timer.h";
#include "../Cheval/src/Headers/DataStructures/Transforms.h"
#include "../Cheval/src/Headers/Integrators/Integrator.h"
#include "../Cheval/src/Headers/Models/Lights/Light.h"

int main()
{
	auto timer = Timer();
	timer.start();
	const auto wall_z = 10;
	const auto ray_origin = Point(0, 0, -5);
	const auto canvas_size = 1000;
	const auto wall_size = 7.0f;

	const auto pixel_size = wall_size / canvas_size;

	const auto half = wall_size / 2;

	const auto canvas = Canvas(canvas_size, canvas_size);
	//const auto colour = Colour(1, 0, 0);
	auto shape = std::make_shared<Sphere>();
	shape->material().colour() = Colour(1, 0.2, 1);

	const auto light_position = Point(-10, 10, -10);
	const auto light_colour = Colour(1, 1, 1);
	auto light = point_light(light_position, light_colour);
	
	//auto transform = matrix::shearing(1,0,0,0,0,0) * matrix::scaling(0.5, 1, 1);
	//shape->setTransform(transform);

	for (int y = 0; y < canvas_size-1; y++)
	{
		const auto world_y = half - pixel_size * y;

		for (int x = 0; x < canvas_size - 1; x++)
		{
			const auto world_x = -half + pixel_size * x;
			auto position = Point(world_x, world_y, wall_z);

			auto r = Ray(ray_origin, Tuple::normalize(position - ray_origin));
			auto xs = Intersections();

			shape->intersect(r, xs);
			auto hit = Intersection::hit(xs);
			if (!xs.empty() && hit.object()!= nullptr)
			{
				auto point = r.position(hit.time());
				auto normal = hit.object()->normal_at(point);
				auto eye = -r.direction();
				
				auto colour = Integrator::lighting(hit.object()->material(), light, point, eye, normal);
				canvas.write_pixel(x, y, colour);
			}
		}
	}
	std::cout << "Render Finished (";
	timer.displayElapsedTime();
	std::cout << ")" << std::endl;
	
	const auto* const filename = R"(D:\Documents\Pictures\Cheval\second.jpg)";
	std::cout << "Result:" << canvas.write_file(filename) << std::endl;

	timer.stop();
	
	std::cout << "Total time taken: ";
	timer.displayElapsedTime();
	std::cout << std::endl;
	
}

