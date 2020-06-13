#include "pch.h"

#include "../Cheval/src/Headers/World.h"
#include "../Cheval/src/Headers/DataStructures/Transforms.h"
#include "../Cheval/src/Headers/Models/Shapes/Sphere.h"

/*
 * Scenario: Creating a world
Given w ← world()
Then w contains no objects
And w has no light source
 */

TEST(WorldTests, CreatingWorld)
{
    auto w = World();
    EXPECT_EQ(w.objects().size(), 0);
    EXPECT_EQ(w.lights().size(), 0);
}

/*
 * Scenario: The default world
Given light ← point_light(point(-10, 10, -10), color(1, 1, 1))
And s1 ← sphere() with:
| material.color | (0.8, 1.0, 0.6) |
| material.diffuse | 0.7 |
| material.specular | 0.2 |
And s2 ← sphere() with:
| transform | scaling(0.5, 0.5, 0.5) |
When w ← default_world()
Then w.light = light
And w contains s1
And w contains s2
 */

//Not tested due to limitations with Shape class (No operators)

//TEST(WorldTests, DefaultWorld)
//{
//    auto w = Default_World();
//	auto light = Point_Light(Point(-10, 10, -10), Colour(1, 1, 1));
//	auto s1 = GetShape<Sphere>();
//	s1->material().colour() = Colour(0.8, 1.0, 0.6);
//	s1->material().diffuse() = 0.7;
//	s1->material().specular() = 0.2;
//	auto s2 = GetShape<Sphere>();
//	auto t = matrix::scaling(0.5, 0.5, 0.5);
//	s2->setTransform(t);
//	
//	auto li = w.lights();
//	EXPECT_TRUE(std::find(li.begin(), li.end(), light) != li.end());
//	
//	auto objs = w.objects();
//	EXPECT_TRUE(std::find(objs.begin(), objs.end(), s1) != objs.end());
//	EXPECT_TRUE(std::find(objs.begin(), objs.end(), s2) != objs.end());
//	
//}

/*
Scenario: Intersect a world with a ray
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
When xs ← intersect_world(w, r)
Then xs.count = 4
And xs[0].t = 4
And xs[1].t = 4.5
And xs[2].t = 5.5
And xs[3].t = 6
*/

TEST(WorldTests, IntersectRayWithWorld)
{
    auto w = Default_World();
    const auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));

    auto xs = w.intersect(r);

    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].time(), 4);
    EXPECT_EQ(xs[1].time(), 4.5);
    EXPECT_EQ(xs[2].time(), 5.5);
    EXPECT_EQ(xs[3].time(), 6);
	
}

/*
 * Scenario: Shading an intersection
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
And shape ← the first object in w
And i ← intersection(4, shape)
When comps ← prepare_computations(i, r)
And c ← shade_hit(w, comps)
Then c = color(0.38066, 0.47583, 0.2855)
*/

TEST(WorldTests, ShadingIntersection)
{
    auto w = Default_World();
    const auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    const auto shape = w.objects()[0];
    auto i = Intersection(4, shape);
	i.prepare_computations(r);

    auto c = w.shade_hit(i);

    EXPECT_EQ(c, Colour(0.38066f, 0.47583f, 0.2855f));
}

    /*
    Scenario: Shading an intersection from the inside
    Given w ← default_world()
    And w.light ← point_light(point(0, 0.25, 0), color(1, 1, 1))
    And r ← ray(point(0, 0, 0), vector(0, 0, 1))
    And shape ← the second object in w
    And i ← intersection(0.5, shape)
    When comps ← prepare_computations(i, r)
    And c ← shade_hit(w, comps)
    Then c = color(0.90498, 0.90498, 0.90498)
     */

TEST(WorldTests, ShadingIntersectionInside)
{
    auto w = Default_World();
    w.lights()[0] = Point_Light(Point(0, 0.25, 0), Colour(1, 1, 1));
    const auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    const auto shape = w.objects()[1];
    auto i = Intersection(0.5, shape);
    i.prepare_computations(r);

    auto c = w.shade_hit(i);

    EXPECT_EQ(c, Colour(0.90498f, 0.90498f, 0.90498f));
}

/*
 * Scenario: The color when a ray misses
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 1, 0))
When c ← color_at(w, r)
Then c = color(0, 0, 0)
 */

TEST(WorldTests, WhenRayMisses)
{
    auto w = Default_World();
    const auto r = Ray(Point(0, 0, -5), Vector(0, 1, 0));
    auto c = w.colour_at(r);

    EXPECT_EQ(c, Colour::Black());
}

/*
 * Scenario: The color when a ray hits
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
When c ← color_at(w, r)
Then c = color(0.38066, 0.47583, 0.2855)
 */

TEST(WorldTests, WhenRayHits)
{
    auto w = Default_World();
    const auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto c = w.colour_at(r);

    EXPECT_EQ(c, Colour(0.38066f, 0.47583f, 0.2855f));
}

/*
 * Scenario: The color with an intersection behind the ray
Given w ← default_world()
And outer ← the first object in w
And outer.material.ambient ← 1
And inner ← the second object in w
And inner.material.ambient ← 1
And r ← ray(point(0, 0, 0.75), vector(0, 0, -1))
When c ← color_at(w, r)
Then c = inner.material.color
 */

TEST(WorldTests, WhenRayHitsCorrectShape)
{
    auto w = Default_World();
    auto outer = w.objects()[0];
    outer->material().ambient() = 1;
    auto inner = w.objects()[1];
    inner->material().ambient() = 1;
    const auto r = Ray(Point(0, 0, 0.75), Vector(0, 0, -1));
	
    auto c = w.colour_at(r);

    EXPECT_EQ(c, inner->material().colour());
}