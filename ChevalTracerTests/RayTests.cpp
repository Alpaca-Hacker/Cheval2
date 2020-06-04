#include "pch.h"


#include "../Cheval/src/Headers/DataStructures/Tuple.h"
#include "../Cheval/src/Headers/Models/Ray.h"

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
 * Scenario: Computing a point from a distance
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