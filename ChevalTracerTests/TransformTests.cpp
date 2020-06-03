#include "pch.h"

#include "../Cheval/transforms.h"
#include "../Cheval/Utils.h"
/*
 * Scenario: Multiplying by a translation matrix
   Given transform ← translation(5, -3, 2)
   And p ← point(-3, 4, 5)
   Then transform * p = point(2, 1, 7)
   */

TEST(TransformTests, TranslationTest)
{
    auto trans = matrix::translation(5, -3, 2);
    auto point = Point(-3, 4, 5);

	EXPECT_EQ(trans * point, Point(2, 1, 7));
}

/*
Scenario: Multiplying by the inverse of a translation matrix
Given transform ← translation(5, -3, 2)
And inv ← inverse(transform)
And p ← point(-3, 4, 5)
Then inv * p = point(-8, 7, 3)
*/

TEST(TransformTests, TranslationInverseTest)
{
    auto trans = matrix::translation(5, -3, 2);
    auto inv = trans.inverse();
    auto point = Point(-3, 4, 5);

    EXPECT_EQ(inv * point, Point(-8, 7, 3));
}

/*
 * Scenario: Translation does not affect vectors
      Given transform ← translation(5, -3, 2)
      And v ← vector(-3, 4, 5)
      Then transform * v = v
 */

TEST(TransformTests, TranslateWithVecorsTest)
{
    auto trans = matrix::translation(5, -3, 2);
    auto v = Vector(-3, 4, 5);

    EXPECT_EQ(trans * v, v);
}

    /*
 * Scenario: A scaling matrix applied to a point
   Given transform ← scaling(2, 3, 4)
   And p ← point(-4, 6, 8)
   Then transform * p = point(-8, 18, 32)
   */

TEST(TransformTests, ScalingTest)
{
    auto trans = matrix::scaling(2, 3, 4);
    auto point = Point(-4, 6, 8);

    EXPECT_EQ(trans * point, Point(-8, 18, 32));

}
/*
 *         Scenario: A scaling matrix applied to a vector
        Given transform ← scaling(2, 3, 4)
        And v ← vector(-4, 6, 8)
        Then transform * v = vector(-8, 18, 32)
 */
TEST(TransformTests, ScalingWithVectorTest)
{
    auto trans = matrix::scaling(2, 3, 4);
    auto vector = Vector(-4, 6, 8);

    EXPECT_EQ(trans * vector, Vector(-8, 18, 32));
}

/*
Scenario: Multiplying by the inverse of a scaling matrix
Given transform ← scaling(2, 3, 4)
And inv ← inverse(transform)
And v ← vector(-4, 6, 8)
Then inv * v = vector(-2, 2, 2)
*/

TEST(TransformTests, ScalingInverseWithVectorTest)
{
    auto trans = matrix::scaling(2, 3, 4);
    auto vector = Vector(-4, 6, 8);

    auto inv = trans.inverse();

    EXPECT_EQ(inv * vector, Vector(-2,2,2));
}

/*
 * Scenario: Reflection is scaling by a negative value
   Given transform ← scaling(-1, 1, 1)
   And p ← point(2, 3, 4)
   Then transform * p = point(-2, 3, 4)
 */
TEST(TransformTests, ScalingReflectionTest)
{
    auto trans = matrix::scaling(-1, 1, 1);
    auto point = Point(2,3,4);

    EXPECT_EQ(trans * point, Point(-2,3,4));
}

/*
 * Scenario: Rotating a point around the x axis
   Given p ← point(0, 1, 0)
   And half_quarter ← rotation_x(π / 4)
   And full_quarter ← rotation_x(π / 2)
   Then half_quarter * p = point(0, √2/2, √2/2)
   And full_quarter * p = point(0, 0, 1)
 */

TEST(TransformTests, RotXTest)
{
    auto p = Point(0, 1, 0);
    auto eighth = matrix::rotation_x(PIDIV4);
	auto quarter = matrix::rotation_x(PIDIV2);

    EXPECT_EQ(eighth * p, Point(0, SQRT2DIV2, SQRT2DIV2));
    EXPECT_EQ(quarter * p, Point(0, 0, 1));
}

/*
 * Scenario: Rotating a point around the y axis
   Given p ← point(0, 0, 1)
   And half_quarter ← rotation_y(π / 4)
   And full_quarter ← rotation_y(π / 2)
   Then half_quarter * p = point(√2/2, 0, √2/2)
   And full_quarter * p = point(1, 0, 0)
 */

TEST(TransformTests, RotYTest)
{
    auto p = Point(0, 0, 1);
    auto eighth = matrix::rotation_y(PIDIV4);
    auto quarter = matrix::rotation_y(PIDIV2);

    EXPECT_EQ(eighth * p, Point( SQRT2DIV2, 0, SQRT2DIV2));
    EXPECT_EQ(quarter * p, Point(1, 0, 0));
}

/*
 * Scenario: Rotating a point around the z axis
   Given p ← point(0, 1, 0)
   And half_quarter ← rotation_z(π / 4)
   And full_quarter ← rotation_z(π / 2)
   Then half_quarter * p = point(-√2/2, √2/2, 0)
   And full_quarter * p = point(-1, 0, 0)
 */

TEST(TransformTests, RotZTest)
{
    auto p = Point(0, 1, 0);
    auto eighth = matrix::rotation_z(PIDIV4);
    auto quarter = matrix::rotation_z(PIDIV2);

    EXPECT_EQ(eighth * p, Point(-SQRT2DIV2, SQRT2DIV2,0));
    EXPECT_EQ(quarter * p, Point(-1, 0, 0));
}

/*
 * Scenario: A shearing transformation moves x in proportion to y
   Given transform ← shearing(1, 0, 0, 0, 0, 0)
   And p ← point(2, 3, 4)
   Then transform * p = point(5, 3, 4)
 */

TEST(TransformTests, ShearTestXY)
{
    auto transform = matrix::shearing(1, 0, 0, 0, 0, 0);
    auto p = Point(2, 3, 4);

    EXPECT_EQ(transform * p, Point(5, 3, 4));
}

/*
 * Scenario: A shearing transformation moves x in proportion to z
   Given transform ← shearing(0, 1, 0, 0, 0, 0)
   And p ← point(2, 3, 4)
   Then transform * p = point(6, 3, 4)
   */

TEST(TransformTests, ShearTestXZ)
{
    auto transform = matrix::shearing(0, 1, 0, 0, 0, 0);
    auto p = Point(2, 3, 4);

    EXPECT_EQ(transform * p, Point(6, 3, 4));
}

/*
   Scenario: A shearing transformation moves y in proportion to x
   Given transform ← shearing(0, 0, 1, 0, 0, 0)
   And p ← point(2, 3, 4)
   Then transform * p = point(2, 5, 4)
   */
TEST(TransformTests, ShearTestYX)
{
    auto transform = matrix::shearing(0, 0, 1, 0, 0, 0);
    auto p = Point(2, 3, 4);

    EXPECT_EQ(transform * p, Point(2, 5, 4));
}
/*
Scenario: A shearing transformation moves y in proportion to z
Given transform ← shearing(0, 0, 0, 1, 0, 0)
And p ← point(2, 3, 4)
Then transform * p = point(2, 7, 4)
 */
TEST(TransformTests, ShearTestYZ)
{
    auto transform = matrix::shearing(0, 0, 0, 1, 0, 0);
    auto p = Point(2, 3, 4);

    EXPECT_EQ(transform * p, Point(2, 7, 4));
}
/*
Scenario: A shearing transformation moves z in proportion to x
Given transform ← shearing(0, 0, 0, 0, 1, 0)
And p ← point(2, 3, 4)
Then transform * p = point(2, 3, 6)
*/
TEST(TransformTests, ShearTestZX)
{
    auto transform = matrix::shearing(0, 0, 0, 0, 1, 0);
    auto p = Point(2, 3, 4);

    EXPECT_EQ(transform * p, Point(2, 3, 6));
}
/*
Scenario: A shearing transformation moves z in proportion to y
Given transform ← shearing(0, 0, 0, 0, 0, 1)
And p ← point(2, 3, 4)
Then transform * p = point(2, 3, 7)
*/
TEST(TransformTests, ShearTestZY)
{
    auto transform = matrix::shearing(0, 0, 0, 0, 0, 1);
    auto p = Point(2, 3, 4);

    EXPECT_EQ(transform * p, Point(2, 3, 7));
}

/*
 * Scenario: Individual transformations are applied in sequence
Given p ← point(1, 0, 1)
And A ← rotation_x(π / 2)
And B ← scaling(5, 5, 5)
And C ← translation(10, 5, 7)
# apply rotation first
When p2 ← A * p
Then p2 = point(1, -1, 0)
# then apply scaling
When p3 ← B * p2
Then p3 = point(5, -5, 0)
# then apply translation
When p4 ← C * p3
Then p4 = point(15, 0, 7)
*/

TEST(TransformTests, TransformsInSeq)
{
    auto p = Point(1, 0, 1);
    auto A = matrix::rotation_x(PIDIV2);
    auto B = matrix::scaling(5, 5, 5);
    auto C = matrix::translation(10, 5, 7);

    auto p2 = A * p;
    EXPECT_EQ(p2, Point(1, -1, 0));

    auto p3 = B * p2;
    EXPECT_EQ(p3, Point(5, -5, 0));

    auto p4 = C * p3;
    EXPECT_EQ(p4, Point(15, 0, 7));
}

/*
Scenario: Chained transformations must be applied in reverse order
Given p ← point(1, 0, 1)
And A ← rotation_x(π / 2)
And B ← scaling(5, 5, 5)
And C ← translation(10, 5, 7)
When T ← C * B * A
Then T * p = point(15, 0, 7)
 */
TEST(TransformTests, TransformsChained)
{
    auto p = Point(1, 0, 1);
    auto A = matrix::rotation_x(PIDIV2);
    auto B = matrix::scaling(5, 5, 5);
    auto C = matrix::translation(10, 5, 7);

    auto T = C * B * A;

    EXPECT_EQ(T * p, Point(15, 0, 7));
}

