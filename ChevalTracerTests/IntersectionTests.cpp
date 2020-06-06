#include "pch.h"

#include "../Cheval/src/Headers/Models/Shapes/Sphere.h"

/*
 * Scenario: An intersection encapsulates t and object
Given s ← sphere()
When i ← intersection(3.5, s)
Then i.t = 3.5
And i.object = s
 */

TEST(IntersectionTests, CreateIntersection)
{
	const auto s = std::make_shared<Sphere>();
	auto i = Intersection(3.5, s);

	EXPECT_EQ(i.time(), 3.5f);
	EXPECT_EQ(i.object(), s);
}

/*
 * Scenario: Aggregating intersections
Given s ← sphere()
And i1 ← intersection(1, s)
And i2 ← intersection(2, s)
When xs ← intersections(i1, i2)
Then xs.count = 2
And xs[0].t = 1
And xs[1].t = 2
 */

TEST(IntersectionTests, IntersectionsWork)
{
    const auto s = std::make_shared<Sphere>();
    const auto i1 = Intersection(1, s);
    const auto i2 = Intersection(2, s);
    auto xs = Intersections(i1, i2);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].time(), 1);
    EXPECT_EQ(xs[1].time(), 2);
}

/*
 * Scenario: Intersect sets the object on the intersection
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0].object = s
And xs[1].object = s
 */

TEST(IntersectionTests, IntersectionHasObjectPointers)
{
    const auto r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    const auto s = std::make_shared<Sphere>();

    auto xs = Intersections();
    s->intersect(r, xs);

    EXPECT_EQ(xs.size(), 2);

    EXPECT_EQ(xs[0].object(), s);
    EXPECT_EQ(xs[1].object(), s);
}

/*
 * Scenario: The hit, when all intersections have positive t
Given s ← sphere()
And i1 ← intersection(1, s)
And i2 ← intersection(2, s)
And xs ← intersections(i2, i1)
When i ← hit(xs)
Then i = i1
*/
TEST(IntersectionTests, HitTestAllPositive)
{
    const auto s = std::make_shared<Sphere>();
    const auto i1 = Intersection(1, s);
    const auto i2 = Intersection(2, s);
	auto xs = Intersections(i1,i2);

    EXPECT_EQ(Intersection::hit(xs), i1);
}
/*
Scenario: The hit, when some intersections have negative t
Given s ← sphere()
And i1 ← intersection(-1, s)
And i2 ← intersection(1, s)
And xs ← intersections(i2, i1)
When i ← hit(xs)
Then i = i2
*/

TEST(IntersectionTests, HitTestSomeNegative)
{
    const auto s = std::make_shared<Sphere>();
    const auto i1 = Intersection(-1, s);
    const auto i2 = Intersection(1, s);
    auto xs = Intersections(i1,i2);

    EXPECT_EQ(Intersection::hit(xs), i2);
}

/*
Scenario: The hit, when all intersections have negative t
Given s ← sphere()
And i1 ← intersection(-2, s)
And i2 ← intersection(-1, s)
And xs ← intersections(i2, i1)
When i ← hit(xs)
Then i is nothing
*/
TEST(IntersectionTests, HitTestAllNegative)
{
    const auto s = std::make_shared<Sphere>();
    const auto i1 = Intersection(-2, s);
    const auto i2 = Intersection(-1, s);
    auto xs = Intersections(i1,i2 );

    EXPECT_EQ(Intersection::hit(xs).object(), nullptr);
}
/*
Scenario: The hit is always the lowest nonnegative intersection
Given s ← sphere()
And i1 ← intersection(5, s)
And i2 ← intersection(7, s)
And i3 ← intersection(-3, s)
And i4 ← intersection(2, s)
And xs ← intersections(i1, i2, i3, i4)
When i ← hit(xs)
Then i = i4
 */
TEST(IntersectionTests, HitTestLotsOfXs)
{
    const auto s = std::make_shared<Sphere>();
    const auto i1 = Intersection(5, s);
    const auto i2 = Intersection(7, s);
    const auto i3 = Intersection(-3, s);
    const auto i4 = Intersection(2, s);
    auto xs = Intersections(i1,i2, i3, i4 );

    EXPECT_EQ(Intersection::hit(xs), i4);
}