#include "pch.h"


#include "../Cheval/src/Headers/DataStructures/Transforms.h"
#include "../Cheval/src/Headers/Models/Shapes/Sphere.h"

/*
 * Scenario: A sphere's default transformation
Given s ← sphere()
Then s.transform = identity_matrix
*/
TEST(SphereTests, DefaultTransform)
{
	auto s = std::make_shared<Sphere>();
	
    EXPECT_EQ(s->transform(), Matrix::identity());
}
/*
Scenario: Changing a sphere's transformation
Given s ← sphere()
And t ← translation(2, 3, 4)
When set_transform(s, t)
Then s.transform = t
 */

TEST(SphereTests, SetTransform)
{
    auto s = std::make_shared<Sphere>();
   auto t = matrix::translation(2, 3, 4);
   s->setTransform(t);

    EXPECT_EQ(s->transform(), t);
}

/*
 * Scenario: Intersecting a scaled sphere with a ray
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
And s ← sphere()
When set_transform(s, scaling(2, 2, 2))
And xs ← intersect(s, r)
Then xs.count = 2
And xs[0].t = 3
And xs[1].t = 7
*/
TEST(SphereTests, RayIntersectWithScaledSphere)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = std::make_shared<Sphere>();
    auto t = matrix::scaling(2, 2, 2);
    s->setTransform(t);

	auto xs = Intersections();
    s->intersect(r, xs);

	EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].time(), 3);
    EXPECT_EQ(xs[1].time(), 7);
}
/*
Scenario: Intersecting a translated sphere with a ray
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
And s ← sphere()
When set_transform(s, translation(5, 0, 0))
And xs ← intersect(s, r)
Then xs.count = 0
 */

TEST(SphereTests, RayIntersectWithTranslatedSphere)
{
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = std::make_shared<Sphere>();
	auto t = matrix::translation(5, 0, 0);
    s->setTransform(t);

    auto xs = Intersections();
    s->intersect(r, xs);

    EXPECT_EQ(xs.size(), 0);
}
