#include "pch.h"



#include "../Cheval/src/Headers/DataStructures/Transforms.h"
#include "../Cheval/src/Headers/DataStructures/Tuple.h"
#include "../Cheval/src/Headers/Models/Ray.h"
#include "../Cheval/src/Headers/Models/Shapes/Sphere.h"

/*
 * Scenario: Creating and querying a ray
Given origin ← point(1, 2, 3)
And direction ← vector(4, 5, 6)
When r ← ray(origin, direction)
Then r.origin = origin
And r.direction = direction
 */
TEST(RayTests, CreateRay)
{
	const auto origin = Point(1, 2, 3);
	const auto direction = Vector(4, 5, 6);
    auto r = Ray(origin, direction);

    EXPECT_EQ(r.origin(), origin);
    EXPECT_EQ(r.direction(), direction);
}

/*
 * Scenario: Computing a point from a time
Given r ← ray(point(2, 3, 4), vector(1, 0, 0))
Then position(r, 0) = point(2, 3, 4)
And position(r, 1) = point(3, 3, 4)
And position(r, -1) = point(1, 3, 4)
And position(r, 2.5) = point(4.5, 3, 4)
 */

TEST(RayTests, RayPosition)
{
    auto r = Ray(Point(2, 3, 4), Vector(1, 0, 0));
    auto start = r.position(0);
	
    EXPECT_EQ(r.position(0), Point(2, 3, 4));
    EXPECT_EQ(r.position(1), Point(3, 3, 4));
    EXPECT_EQ(r.position(-1), Point(1, 3, 4));
    EXPECT_EQ(r.position(2.5), Point(4.5, 3, 4));
}

/*
 * Scenario: A ray intersects a sphere at two points
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = 4.0
And xs[1] = 6.0
 */

TEST(RayTests, RayVsSphereTwoPoints)
{
	const auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	const auto s = std::make_shared<Sphere>();

    auto xs = std::vector<Intersection>();
    s->intersect(r,xs);

    EXPECT_EQ(xs.size(), 2);

    EXPECT_FLOAT_EQ(xs[0].time(), 4.0f);
    EXPECT_FLOAT_EQ(xs[1].time(), 6.0f);
}

/*
 * Scenario: A ray intersects a sphere at a tangent
Given r ← ray(point(0, 1, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = 5.0
And xs[1] = 5.0
 */

TEST(RayTests, RayVsSphereTangent)
{
	const auto r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
	const auto s = std::make_shared<Sphere>();

    auto xs = std::vector<Intersection>();
    s->intersect(r, xs);

    EXPECT_EQ(xs.size(), 2);

    EXPECT_FLOAT_EQ(xs[0].time(), 5.0f);
    EXPECT_FLOAT_EQ(xs[1].time(), 5.0f);
}

/*
 * Scenario: A ray misses a sphere
Given r ← ray(point(0, 2, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 0
 */

TEST(RayTests, RayVsSphereMiss)
{
	const auto r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
	const auto s = std::make_shared<Sphere>();

    auto xs = std::vector<Intersection>();
    s->intersect(r, xs);

    EXPECT_EQ(xs.size(), 0);

}

/*
 * Scenario: A ray originates inside a sphere
Given r ← ray(point(0, 0, 0), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = -1.0
And xs[1] = 1.0
 */

TEST(RayTests, RayVsSphereFromMiddle)
{
	const auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
	const auto s = std::make_shared<Sphere>();

    auto xs = std::vector<Intersection>();
    s->intersect(r, xs);

    EXPECT_EQ(xs.size(), 2);

    EXPECT_FLOAT_EQ(xs[0].time(), -1.0f);
    EXPECT_FLOAT_EQ(xs[1].time(), 1.0f);

}

/*
 * Scenario: A sphere is behind a ray
Given r ← ray(point(0, 0, 5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = -6.0
And xs[1] = -4.0
 */

TEST(RayTests, RayVsSphereFromBehind)
{
	const auto r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
	const auto s = std::make_shared<Sphere>();

    auto xs = Intersections();
    s->intersect(r, xs);

    EXPECT_EQ(xs.size(), 2);

    EXPECT_FLOAT_EQ(xs[0].time(), -6.0f);
    EXPECT_FLOAT_EQ(xs[1].time(), -4.0f);
}
/*
 * Scenario: Translating a ray
Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
And m ← translation(3, 4, 5)
When r2 ← transform(r, m)
Then r2.origin = point(4, 6, 8)
And r2.direction = vector(0, 1, 0)
*/
TEST(RayTests, RayTranslating)
{
    const auto r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
    const auto m = transforms::translation(3, 4, 5);

    const auto r2 = Ray::transform(r, m);

    EXPECT_EQ(r2.origin(), Point(4, 6, 8));
    EXPECT_EQ(r2.direction(), Vector(0, 1, 0));
}
/*
Scenario: Scaling a ray
Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
And m ← scaling(2, 3, 4)
When r2 ← transform(r, m)
Then r2.origin = point(2, 6, 12)
And r2.direction = vector(0, 3, 0)
 */

TEST(RayTests, RayScale)
{
    const auto r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
    const auto m = transforms::scaling(2,3, 4);

    const auto r2 = Ray::transform(r, m);

    EXPECT_EQ(r2.origin(), Point(2, 6, 12));
    EXPECT_EQ(r2.direction(), Vector(0, 3, 0));
}
