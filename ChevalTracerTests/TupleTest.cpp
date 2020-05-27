#include "pch.h"

#include "../Cheval/Tuple.h"

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
	auto Sut = Tuple(4.3, -4.2, 3.1, 1.0);
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
	auto Sut = Tuple(4.3, -4.2, 3.1, 0.0);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 0.0f);
	EXPECT_FALSE(Sut.is_point());
	EXPECT_TRUE(Sut.is_vector());
}

TEST(TupleTests, PointCanBeCreated)
{
	auto Sut = Point(4.3, -4.2, 3.1);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 1.0f);
	EXPECT_TRUE(Sut.is_point());
	EXPECT_FALSE(Sut.is_vector());
}

TEST(TupleTests, VectorCanBeCreated)
{
	auto Sut = Vector(4.3, -4.2, 3.1);
	EXPECT_EQ(Sut.X(), 4.3f);
	EXPECT_EQ(Sut.Y(), -4.2f);
	EXPECT_EQ(Sut.Z(), 3.1f);
	EXPECT_EQ(Sut.W(), 0.0f);
	EXPECT_FALSE(Sut.is_point());
	EXPECT_TRUE(Sut.is_vector());
}