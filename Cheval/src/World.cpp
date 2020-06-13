#include "./Headers/World.h"


#include "Headers/DataStructures/Transforms.h"
#include "Headers/Integrators/Integrator.h"
#include "Headers/Models/Shapes/Sphere.h"

std::vector<Intersection> World::intersect(const Ray& ray)
{
	auto xs = Intersections();
	for (const auto& shape : objects())
	{
		shape->intersect(ray, xs);
	}
	std::sort(xs.begin(), xs.end());
	return xs;
}

Colour World::shade_hit(const Intersection& hit)
{
	auto colour = Colour::Black();

	for (auto light : lights_)
	{
		colour = colour + Integrator::lighting(hit.object()->material(), light, hit.point(), hit.eyeV(), hit.normalV());
	}
	return colour;
}

Colour World::colour_at(const Ray& ray)
{
	auto xs = intersect(ray);
	auto hit = Intersection::hit(xs);
	if (hit.object() == nullptr)
	{
		return Colour::Black();
	}
	hit.prepare_computations(ray);
	return shade_hit(hit);
}

World Default_World()
{
	const auto light = Point_Light(Point(-10, 10, -10), Colour(1, 1, 1));
	auto s1 = GetShape<Sphere>();
	s1->material().colour() = Colour(0.8, 1.0, 0.6);
	s1->material().diffuse() = 0.7;
	s1->material().specular() = 0.2;
	auto s2 = GetShape<Sphere>();
	auto t = transforms::scaling(0.5, 0.5, 0.5);
	s2->setTransform(t);
	
	auto world = World();
	world.add(s1);
	world.add(s2);
	world.add(light);
	
	return world;
}
