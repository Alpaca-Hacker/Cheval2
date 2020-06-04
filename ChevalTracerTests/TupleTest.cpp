#include "pch.h"

#include "../Cheval//src/Headers/Helpers/Utils.h"
#include "../Cheval//src/Headers/Models/Colour.h"
#include "../Cheval/src/Headers/DataStructures/Tuple.h"

TEST(TupleTests, NewTupleIsZero)
{
	auto Sut = Tuple();
	EXPECT_EQ(Sut.X(), 0.0f);
	EXPECT_EQ(Sut.Y(), 0.0f);
	EXPECT_EQ(Sut.Z(), 0.0f);
	EXPECT_EQ(Sut.W(), 0.0f);
}

/*
 * Scenario: A tuple with w=1.0 is a point
Given a ← tuple(4.3, -4.2, 3.1, 1.0)
Then a.x = 4.3
And a.y = -4.2
And a.z = 3.1
And a.w = 1.0
And a is a point
And a is not a vector
*/
TEST(TupleTests, TupleIsPointWhenWIsOne)
{
	auto Sut = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 1.0f);
	EXPECT_TRUE(Sut.is_point());
	EXPECT_FALSE(Sut.is_vector());
}

/*
Scenario: A tuple with w=0 is a vector
Given a ← tuple(4.3, -4.2, 3.1, 0.0)
Then a.x = 4.3
And a.y = -4.2
And a.z = 3.1
And a.w = 0.0
And a is not a point
And a is a vector
 */

TEST(TupleTests, TupleIsVectorWhenWIsZero)
{
	auto Sut = Tuple(4.3f, -4.2f, 3.1f, 0.0f);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 0.0f);
	EXPECT_FALSE(Sut.is_point());
	EXPECT_TRUE(Sut.is_vector());
}

TEST(TupleTests, PointCanBeCreated)
{
	auto Sut = Point(4.3f, -4.2f, 3.1f);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 1.0f);
	EXPECT_TRUE(Sut.is_point());
	EXPECT_FALSE(Sut.is_vector());
}

TEST(TupleTests, VectorCanBeCreated)
{
	auto Sut = Vector(4.3f, -4.2f, 3.1f);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 0.0f);
	EXPECT_FALSE(Sut.is_point());
	EXPECT_TRUE(Sut.is_vector());
}

TEST(TupleTests, TuplesCanBeEqual)
{
	auto Sut1 = Point(1.0f, 2.0f, 3.0f);
	auto Sut2 = Point(1.0f, 2.0f, 3.0f);
	auto Sut3 = Vector(1.0f, 2.0f, 3.0f);
	EXPECT_TRUE(Sut1 == Sut2);
	EXPECT_FALSE(Sut1 == Sut3);
	EXPECT_TRUE(Sut2 != Sut3);
}

/*
 * Scenario: Adding two tuples
Given a1 ← tuple(3, -2, 5, 1)
And a2 ← tuple(-2, 3, 1, 0)
Then a1 + a2 = tuple(1, 1, 6, 1)
 */

TEST(TupleTests, TuplesAdd)
{
	auto a1 = Tuple(3.0f, -2.0f, 5.0f, 1.0f);
	auto a2 = Tuple(-2.0f, 3.0f, 1.0f, 0.0f);

	const auto expected = Tuple(1.0f, 1.0f, 6.0f, 1.0f);
	auto result = a1 + a2;

	EXPECT_TRUE(result == expected);
}

/*
 * Scenario: Subtracting two points
Given p1 ← point(3, 2, 1)
And p2 ← point(5, 6, 7)
Then p1 - p2 = vector(-2, -4, -6)
 */

TEST(TupleTests, PointsSubtract)
{
	auto a1 = Point(3.0f, 2.0f, 1.0f);
	auto a2 = Point(5.0f, 6.0f, 7.0f);

	const auto expected = Vector(-2.0f, -4.0f, -6.0f);
	auto result = a1 - a2;

	EXPECT_TRUE(result == expected);
}

/*
 * Scenario: Subtracting a vector from a point
Given p ← point(3, 2, 1)
And v ← vector(5, 6, 7)
Then p - v = point(-2, -4, -6)
 */

TEST(TupleTests, SubtractVectorFromPoint)
{
	auto a1 = Point(3.0f, 2.0f, 1.0f);
	auto a2 = Vector(5.0f, 6.0f, 7.0f);

	const auto expected = Point(-2.0f, -4.0f, -6.0f);
	auto result = a1 - a2;

	EXPECT_TRUE(result == expected);
}

/*
 * Scenario: Subtracting two vectors
Given v1 ← vector(3, 2, 1)
And v2 ← vector(5, 6, 7)
Then v1 - v2 = vector(-2, -4, -6)
 */

TEST(TupleTests, VectorSubtract)
{
	auto a1 = Vector(3.0f, 2.0f, 1.0f);
	auto a2 = Vector(5.0f, 6.0f, 7.0f);

	const auto expected = Vector(-2.0f, -4.0f, -6.0f);
	auto result = a1 - a2;

	EXPECT_TRUE(result == expected);
}

/*
 * Scenario: Negating a tuple
Given a ← tuple(1, -2, 3, 1)
Then -a = tuple(-1, 2, -3, 1)
 */

TEST(TupleTests, NegateTuple)
{
	auto a = Tuple(1.0f, -2.0f, 3.0f, 1.0f);

	const auto expected = Tuple(-1.0f, 2.0f, -3.0f, 1.0f);
	auto result = -a;

	EXPECT_TRUE(result == expected);
}

/*
 *Scenario: Computing the magnitude of vector(1, 0, 0)
Given v ← vector(1, 0, 0)
Then magnitude(v) = 1
 * Scenario: Computing the magnitude of vector(0, 1, 0)
Given v ← vector(0, 1, 0)
Then magnitude(v) = 1
Scenario: Computing the magnitude of vector(0, 0, 1)
Given v ← vector(0, 0, 1)
Then magnitude(v) = 1
Scenario: Computing the magnitude of vector(1, 2, 3)
Given v ← vector(1, 2, 3)
Then magnitude(v) = √14
Scenario: Computing the magnitude of vector(-1, -2, -3)
Given v ← vector(-1, -2, -3)
Then magnitude(v) = √14
 */

TEST(TupleTests, MagnitudeIsCorrect)
{
	auto a = Vector(1.0f, 0.0f, 0.0f);
	EXPECT_EQ(a.magnitude(), 1.0f);
	auto b = Vector(0.0f, 1.0f, 0.0f);
	EXPECT_EQ(b.magnitude(), 1.0f);
	auto c = Vector(0.0f, 0.0f, 1.0f);
	EXPECT_EQ(c.magnitude(), 1.0f);
	auto d = Vector(1.0f, 2.0f, 3.0f);
	EXPECT_EQ(d.magnitude(), std::sqrtf(14.0f));
	auto e = Vector(-1.0f, -2.0f, -3.0f);
	EXPECT_EQ(e.magnitude(), std::sqrtf(14.0f));
}

/*
 * Scenario: Normalizing vector(4, 0, 0) gives (1, 0, 0)
Given v ← vector(4, 0, 0)
Then normalize(v) = vector(1, 0, 0)

Scenario: Normalizing vector(1, 2, 3)
Given v ← vector(1, 2, 3)
# vector(1/√14, 2/√14, 3/√14)
Then normalize(v) = approximately vector(0.26726, 0.53452, 0.80178)
 */

TEST(TupleTests, NormalizeIsCorrectForOneDirection)
{
	auto v = Vector(4.0f, 0.0f, 0.0f);
	EXPECT_TRUE(Tuple::normalize(v) == Vector(1.0f, 0.0f, 0.0f));
}

TEST(TupleTests, NormalizeIsCorrectForThreeDirections)
{
	auto v = Vector(1.0f, 2.0f, 3.0f);
	auto sqrt14 = std::sqrtf(14.0f);
	EXPECT_TRUE(Tuple::normalize(v) == Vector(1.0f /sqrt14, 2.0f /sqrt14, 3.0f /sqrt14));
}

/*
 * Scenario: The magnitude of a normalized vector
Given v ← vector(1, 2, 3)
When norm ← normalize(v)
Then magnitude(norm) = 1
 */
TEST(TupleTests, NormalizeMagnitudeIs1)
{
	auto v = Vector(1.0f, 2.0f, 3.0f);
	auto norm = Tuple::normalize(v);
	EXPECT_TRUE(Equals(norm.magnitude(), 1.0f));
}

/*
 * Scenario: The dot product of two tuples
Given a ← vector(1, 2, 3)
And b ← vector(2, 3, 4)
Then dot(a, b) = 20
 */

TEST(TupleTests, DotProduct)
{
	auto a = Vector(1.0f, 2.0f, 3.0f);
	auto b = Vector(2.0f, 3.0f, 4.0f);
	EXPECT_EQ(Tuple::dot(a, b), 20.0f);
}

/*
Scenario: The cross product of two vectors
Given a ← vector(1, 2, 3)
And b ← vector(2, 3, 4)
Then cross(a, b) = vector(-1, 2, -1)
And cross(b, a) = vector(1, -2, 1)
*/

TEST(TupleTests, CrossProduct)
{
	const auto a = Vector(1.0f, 2.0f, 3.0f);
	const auto b = Vector(2.0f, 3.0f, 4.0f);

	EXPECT_TRUE(Tuple::cross(a, b) == Vector(-1.0f, 2.0f, -1.0f));
	EXPECT_TRUE(Tuple::cross(b, a) == Vector(1.0f, -2.0f, 1.0f));
}

/*Scenario: Adding colors
Given c1 ← color(0.9, 0.6, 0.75)
And c2 ← color(0.7, 0.1, 0.25)
Then c1 + c2 = color(1.6, 0.7, 1.0)
*/
TEST(ColourTests, AddColours)
{
	auto c1 = Colour(0.9f, 0.6f, 0.75f);
	auto c2 = Colour(0.7f, 0.1f, 0.25f);

	auto result = c1 + c2;
	const auto expected = Colour(1.6f, 0.7f, 1.0f);
	EXPECT_TRUE(result == expected);
}


/*
Scenario: Subtracting colors
Given c1 ← color(0.9, 0.6, 0.75)
And c2 ← color(0.7, 0.1, 0.25)
Then c1 - c2 = color(0.2, 0.5, 0.5)
*/
TEST(ColourTests, SubtractColours)
{
	auto c1 = Colour(0.9f, 0.6f, 0.75f);
	auto c2 = Colour(0.7f, 0.1f, 0.25f);

	auto result = c1 - c2;
	const auto expected = Colour(0.2f, 0.5f, 0.5f);
	EXPECT_TRUE(result == expected);
}

/*
Scenario: Multiplying a color by a scalar
Given c ← color(0.2, 0.3, 0.4)
Then c * 2 = color(0.4, 0.6, 0.8)*/
TEST(ColourTests, MultiColour)
{
	const auto c = Colour(0.2f, 0.3f, 0.4f);

	auto result = c * 2.0f;
	const auto expected = Colour(0.4f, 0.6f, 0.8f);
	
	EXPECT_TRUE(result == expected);
}
/*
 * Scenario: Multiplying colors
Given c1 ← color(1, 0.2, 0.4)
And c2 ← color(0.9, 1, 0.1)
Then c1 * c2 = color(0.9, 0.2, 0.04)
 */

TEST(ColourTests, MultiplyColours)
{
	auto c1 = Colour(1.0f, 0.2f, 0.4f);
	auto c2 = Colour(0.9f, 1.0f, 0.1f);

	auto result = c1 * c2;
	const auto expected = Colour(0.9f, 0.2f, 0.04f);
	EXPECT_TRUE(result == expected);
}


