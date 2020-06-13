#pragma once
#include <vector>

#include "Models/Lights/Light.h"
#include "Models/Shapes/Shape.h"

class World
{
public:
	World()
	= default;

	std::vector<ShapePtr> const& objects() const { return objects_; }
	std::vector<ShapePtr>& objects() { return objects_; }

	std::vector<Light> const& lights() const { return lights_; }
	std::vector<Light>& lights() { return lights_; }

	void add(ShapePtr const& s) { objects_.push_back(s); }
	void add(Light const& s) { lights_.push_back(s); }
	std::vector<Intersection> intersect(const Ray& ray);
	Colour shade_hit(const Intersection& intersection);
	Colour colour_at(const Ray& ray);

private:
	std::vector<ShapePtr> objects_;
	std::vector<Light> lights_;
};

World Default_World();

