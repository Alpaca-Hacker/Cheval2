#include "pch.h"


#include "../Cheval/src/Headers/DataStructures/Transforms.h"
#include "../Cheval/src/Headers/Helpers/Utils.h"
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

/*
 * Scenario: The normal on a sphere at a point on the x axis
Given s ← sphere()
When n ← normal_at(s, point(1, 0, 0))
Then n = vector(1, 0, 0)
*/
TEST(SphereTests, NormalOnXAxis)
{
    auto s = std::make_shared<Sphere>();
    auto n = s->normal_at(Point(1, 0, 0));

    EXPECT_EQ(n, Vector(1, 0, 0));
}
/*
Scenario: The normal on a sphere at a point on the y axis
Given s ← sphere()
When n ← normal_at(s, point(0, 1, 0))
Then n = vector(0, 1, 0)
*/
TEST(SphereTests, NormalOnYAxis)
{
    auto s = std::make_shared<Sphere>();
    auto n = s->normal_at(Point(0, 1, 0));

    EXPECT_EQ(n, Vector(0, 1, 0));
}
/*
Scenario: The normal on a sphere at a point on the z axis
Given s ← sphere()
When n ← normal_at(s, point(0, 0, 1))
Then n = vector(0, 0, 1)
*/
TEST(SphereTests, NormalOnZAxis)
{
    auto s = std::make_shared<Sphere>();
    auto n = s->normal_at(Point(0, 0, 1));

    EXPECT_EQ(n, Vector(0, 0, 1));
}
/*
Scenario: The normal on a sphere at a nonaxial point
Given s ← sphere()
When n ← normal_at(s, point(√3/3, √3/3, √3/3))
Then n = vector(√3/3, √3/3, √3/3)
And n = normalize(n)
 */

TEST(SphereTests, NormalOnNonaxial)
{
	const auto rt3div3 = std::sqrtf(3) / 3.0f;
    auto s = std::make_shared<Sphere>();
    auto n = s->normal_at(Point(rt3div3, rt3div3, rt3div3));

    EXPECT_EQ(n, Vector(rt3div3, rt3div3, rt3div3));
    EXPECT_EQ(Tuple::normalize(n), n);
}

/*
 * Scenario: Computing the normal on a translated sphere
Given s ← sphere()
And set_transform(s, translation(0, 1, 0))
When n ← normal_at(s, point(0, 1.70711, -0.70711))
Then n = vector(0, 0.70711, -0.70711)
*/
TEST(SphereTests, NormalOnTranslatedSphere)
{
    auto s = std::make_shared<Sphere>();
	auto t = matrix::translation(0, 1, 0);

	s->setTransform(t);
	
    auto n = s->normal_at(Point(0, 1.70711, -0.70711));

    EXPECT_EQ(n, Vector(0, 0.70711, -0.70711));
}
/*
Scenario: Computing the normal on a transformed sphere
Given s ← sphere()
And m ← scaling(1, 0.5, 1) * rotation_z(π/5)
And set_transform(s, m)
When n ← normal_at(s, point(0, √2/2, -√2/2))
Then n = vector(0, 0.97014, -0.24254)
 */
TEST(SphereTests, NormalOnTransformedSphere)
{
    auto s = std::make_shared<Sphere>();
	
    auto t = matrix::scaling(1, 0.5, 1)* matrix::rotation_z(PI / 5);

    s->setTransform(t);

    auto n = s->normal_at(Point(0, SQRT2DIV2, -SQRT2DIV2));

    EXPECT_EQ(n, Vector(0, 0.97014, -0.24254));
}

/*
 * Scenario: A sphere has a default material
Given s ← sphere()
When m ← s.material
Then m = material()
Scenario: A sphere may be assigned a material
Given s ← sphere()
And m ← material()
And m.ambient ← 1
When s.material ← m
Then s.material = m
 */

TEST(SphereTests, MatTestsOnSphere)
{
    auto s = std::make_shared<Sphere>();
    EXPECT_EQ(s->material(), Material());

    auto m = Material();
    m.ambient() = 1;
    s->material() = m;

    EXPECT_EQ(s->material(), m);
    EXPECT_EQ(s->material().ambient(), 1.0f);
}