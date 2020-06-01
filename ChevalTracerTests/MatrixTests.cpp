#include "pch.h"

#include "../Cheval/Matrix.h"
#include "../Cheval/Tuple.h"

TEST(MatrixTests, Create4x4)
{
	auto m = Matrix(4);
	m(0, 1) = 100;
	EXPECT_EQ(m(0, 1), 100);
}
/*
       * Scenario: Constructing and inspecting a 4x4 matrix
         Given the following 4x4 matrix M:
         | 1    | 2    | 3    | 4    |
         | 5.5  | 6.5  | 7.5  | 8.5  |
         | 9    | 10   | 11   | 12   |
         | 13.5 | 14.5 | 15.5 | 16.5 |
         Then M[0,0] = 1
         And M[0,3] = 4
         And M[1,0] = 5.5
         And M[1,2] = 7.5
         And M[2,2] = 11
         And M[3,0] = 13.5
         And M[3,2] = 15.5
       */
TEST(MatrixTests, Create4x4WithData)
{
	const auto data = std::vector<float>
    {  1.0f,  2.0f,  3.0f, 4.0f,
       5.5f,  6.5f,  7.5f, 8.5f,
       9.0f, 10.0f, 11.0f, 12.0f,
      13.5f, 14.5f, 15.5f, 16.5f };
	auto m = Matrix(4, data);
	EXPECT_EQ(m(0, 0), 1.0f);
    EXPECT_EQ(m(0, 3), 4.0f);
    EXPECT_EQ(m(1, 2), 7.5f);
    EXPECT_EQ(m(2, 2), 11.0f);
    EXPECT_EQ(m(3, 0), 13.5f);
    EXPECT_EQ(m(3, 2), 15.5f);
}

TEST(MatrixTests, Create3x3AllBlank)
{
    auto m = Matrix(3);
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(2, 1), 0);
}

/*
 * Scenario: Matrix equality with identical matrices
   Given the following matrix A:
   | 1 | 2 | 3 | 4 |
   | 5 | 6 | 7 | 8 |
   | 9 | 8 | 7 | 6 |
   | 5 | 4 | 3 | 2 |
   And the following matrix B:
   | 1 | 2 | 3 | 4 |
   | 5 | 6 | 7 | 8 |
   | 9 | 8 | 7 | 6 |
   | 5 | 4 | 3 | 2 |
   Then A = B
 */

TEST(MatrixTests, MatrixEquals)
{
	const auto data = std::vector<float>
    { 1.0f,  2.0f,  3.0f, 4.0f,
      5.0f,  6.0f,  7.0f, 8.0f,
      9.0f, 8.0f, 7.0f, 6.0f,
      5.0f, 4.0f, 3.0f, 2.0f };
	
    auto a = Matrix(4, data);
    auto b = Matrix(4, data);

    EXPECT_TRUE(a == b);
}

TEST(MatrixTests, MatrixNotEquals)
{
    const auto data = std::vector<float>
    { 1.0f,  2.0f,  3.0f, 4.0f,
      5.0f,  6.0f,  7.0f, 8.0f,
      9.0f, 8.0f, 7.0f, 6.0f,
      5.0f, 4.0f, 3.0f, 2.0f };

    auto a = Matrix(4, data);
    auto b = Matrix(4, data);

    b(3, 0) = 0.0f;

    EXPECT_TRUE(a != b);
}

/*
 * Scenario: Multiplying two matrices
   Given the following matrix A:
   | 1 | 2 | 3 | 4 |
   | 5 | 6 | 7 | 8 |
   | 9 | 8 | 7 | 6 |
   | 5 | 4 | 3 | 2 |
   And the following matrix B:
   | -2 | 1 | 2 | 3 |
   | 3 | 2 | 1 | -1 |
   | 4 | 3 | 6 | 5 |
   | 1 | 2 | 7 | 8 |
   Then A * B is the following 4x4 matrix:
   | 20| 22 | 50 | 48 |
   | 44| 54 | 114 | 108 |
   | 40| 58 | 110 | 102 |
   | 16| 26 | 46 | 42 |
 */

TEST(MatrixTests, MatrixMultiply)
{
    const auto data1 = std::vector<float>
    { 1.0f,  2.0f,  3.0f, 4.0f,
      5.0f,  6.0f,  7.0f, 8.0f,
      9.0f,  8.0f,  7.0f, 6.0f,
      5.0f,  4.0f,  3.0f, 2.0f };

    auto a = Matrix(4, data1);

    const auto data2 = std::vector<float>
    { -2.0f, 1.0f, 2.0f,  3.0f,
       3.0f, 2.0f, 1.0f, -1.0f,
       4.0f, 3.0f, 6.0f,  5.0f,
       1.0f, 2.0f, 7.0f,  8.0f
    };
    auto b = Matrix(4, data2);

    const auto expectedData = std::vector<float>
    { 20, 22,  50,  48,
      44, 54, 114, 108,
      40, 58, 110, 102,
      16, 26,  46,  42 };
    const auto expected = Matrix(4, expectedData);

    EXPECT_EQ(a * b, expected);
}

/*
 * Scenario: A matrix multiplied by a tuple
   Given the following matrix A:
   | 1 | 2 | 3 | 4 |
   | 2 | 4 | 4 | 2 |
   | 8 | 6 | 4 | 1 |
   | 0 | 0 | 0 | 1 |
   And b ← tuple(1, 2, 3, 1)
   Then A * b = tuple(18, 24, 33, 1)
 */

TEST(MatrixTests, MatrixAndTupleMultiply)
{
    const auto data = std::vector<float>{
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1,
    };
    auto a = Matrix(4, data);
    auto b = Tuple(1, 2, 3, 1);
    EXPECT_EQ(a * b, Tuple(18, 24, 33, 1));
}

/*
 * Scenario: Multiplying a matrix by the identity matrix
   Given the following matrix A:
   | 0 | 1 | 2 | 4 |
   | 1 | 2 | 4 | 8 |
   | 2 | 4 | 8 | 16 |
   | 4 | 8 | 16 | 32 |
   Then A * identity_matrix = A

 */

TEST(MatrixTests, MatrixAndIdMultiply)
{
    const auto data = std::vector<float>{
    0, 2, 3, 4,
    1, 2, 4, 8,
    2, 4, 8, 16,
    4, 8, 16, 32 };
	
    auto a = Matrix(4, data);
    auto i = Matrix::identity();
    EXPECT_EQ(a * i, a);
}

/*
 * Scenario: Multiplying the identity matrix by a tuple
   Given a ← tuple(1, 2, 3, 4)
   Then identity_matrix * a = a
 */

TEST(MatrixTests, TupleAndIdMultiply)
{
    auto a = Tuple(1,2,3,4);
    auto i = Matrix::identity();
    EXPECT_EQ(a * i, a);
}

/*
 * Scenario ​: Transposing a matrix ​   ​
 * Given ​ the following matrix A: ​  
 * | 0 | 9 | 3 | 0 | ​  
 * | 9 | 8 | 0 | 8 | ​  
 * | 1 | 8 | 5 | 3 | ​  
 * | 0 | 0 | 5 | 8 | ​   ​
 * Then ​
 * transpose(A) is the following matrix: ​  
 * | 0 | 9 | 1 | 0 | ​  
 * | 9 | 8 | 8 | 0 | ​  
 * | 3 | 0 | 5 | 5 | ​  
 * | 0 | 8 | 3 | 8 |
 */

TEST(MatrixTests, MatrixTranspose)
{
    const auto data = std::vector<float>{
    0, 9, 3, 0,
    9, 8, 0, 8,
    1, 8, 5, 3,
    0, 0, 5, 8 };

    auto a = Matrix(4, data);
    const auto expectedData = std::vector<float>
    { 0, 9, 1, 0,
      9, 8, 8, 0,
      3, 0, 5, 5,
      0, 8, 3, 8 };
    const auto expected = Matrix(4, expectedData);

    EXPECT_EQ(a.transpose(), expected);
}

/*
 * Scenario: Transposing the identity matrix
Given A ← transpose(identity_matrix)
Then A = identity_matrix
 */

TEST(MatrixTests, IdMatrixTranspose)
{
    auto a = Matrix::identity();
    EXPECT_EQ(a.transpose(), a);
}

/*
 * Scenario ​: Calculating the determinant of a 2x2 matrix ​   ​
 * Given ​the following 2x2 matrix A: ​  
 * | 1 | 5 | ​  
 * |-3 | 2 | ​   ​
 * Then ​determinant(A) = 17
 */

TEST(MatrixTests, DetOf2x2)
{
    auto a = Matrix(2, std::vector<float>{
        1, 5,
       -3, 2});
    EXPECT_EQ(a.determinant(), 17);
}

/*
 * Scenario: A submatrix of a 3x3 matrix is a 2x2 matrix
Given the following 3x3 matrix A:
|  1 | 5 | 0  |
| -3 | 2 | 7  |
|  0 | 6 | -3 |
Then submatrix(A, 0, 2) is the following 2x2 matrix:
| -3 | 2 |
| 0  | 6 |
*/

TEST(MatrixTests, SubOf3x3)
{
    const auto data = std::vector<float>{
 1, 5, 0, 
-3, 2, 7, 
 0, 6,-3 
 };
    auto a = Matrix(3, data);

    auto expected = Matrix(2, std::vector<float>{-3, 2, 0, 6});
    auto result = a.submatrix(0, 2);

    EXPECT_EQ(result, expected);
}

/*
Scenario: A submatrix of a 4x4 matrix is a 3x3 matrix
Given the following 4x4 matrix A:
| -6 | 1 |  1 | 6 |
| -8 | 5 |  8 | 6 |
| -1 | 0 |  8 | 2 |
| -7 | 1 | -1 | 1 |
Then submatrix(A, 2, 1) is the following 3x3 matrix:
| -6 |  1 | 6 |
| -8 |  8 | 6 |
| -7 | -1 | 1 |
 */

TEST(MatrixTests, SubOf4x4)
{
    const auto data = std::vector<float>{
- 6, 1, 1, 6,
- 8, 5, 8, 6,
- 1, 0, 8, 2,
- 7, 1,-1, 1
    };
    auto a = Matrix(4, data);

    const auto expected = Matrix(3, std::vector<float>{
			-6, 1, 6,
            -8, 8, 6,
            -7, -1, 1,
    });
	
    auto result = a.submatrix(2, 1);

    EXPECT_EQ(result, expected);
}

/*
 * Scenario: Calculating a minor of a 3x3 matrix
   Given the following 3x3 matrix A:
   | 3 |  5 |  0 |
   | 2 | -1 | -7 |
   | 6 | -1 |  5 |
   And B ← submatrix(A, 1, 0)
   Then determinant(B) = 25
   And minor(A, 1, 0) = 25
 */

TEST(MatrixTests, MinorOf3x3)
{
    const auto data = std::vector<float>{
3, 5, 0,
2,-1,-7,
6,-1, 5
};
    auto a = Matrix(3, data);
    auto b = a.submatrix(1, 0);
    EXPECT_EQ(b.determinant(), 25);
    EXPECT_EQ(a.minor(1, 0), 25);
}

/*
 * Scenario: Calculating a cofactor of a 3x3 matrix
   Given the following 3x3 matrix A:
   | 3 | 5  | 0 |
   | 2 | -1 | -7|
   | 6 | -1 | 5 |
   Then minor(A, 0, 0) = -12
   And cofactor(A, 0, 0) = -12
   And minor(A, 1, 0) = 25
   And cofactor(A, 1, 0) = -25
 */

TEST(MatrixTests, CofactorOf3x3)
{
    const auto data = std::vector<float>{
3, 5, 0,
2,-1,-7,
6,-1, 5
    };
    auto a = Matrix(3, data);
    EXPECT_EQ(a.minor(0, 0), -12);
    EXPECT_EQ(a.cofactor(0, 0), -12);
    EXPECT_EQ(a.minor(1, 0), 25);
    EXPECT_EQ(a.cofactor(1, 0), -25);
}

/*
 * Scenario: Calculating the determinant of a 3x3 matrix
   Given the following 3x3 matrix A:
   | 1  | 2 | 6  |
   | -5 | 8 | -4 |
   | 2  | 6 | 4  |
   Then cofactor(A, 0, 0) = 56
   And cofactor(A, 0, 1) = 12
   And cofactor(A, 0, 2) = -46
   And determinant(A) = -196
 */

TEST(MatrixTests, DetOf3x3)
{
    const auto data = std::vector<float>{
    1, 2, 6,
    -5,8,-4,
    2 ,6, 4
    };
    auto a = Matrix(3, data);
    EXPECT_EQ(a.cofactor(0, 0), 56);
    EXPECT_EQ(a.cofactor(0, 1), 12);
    EXPECT_EQ(a.cofactor(0, 2), -46);
    EXPECT_EQ(a.determinant(), -196);
}

/*
 * Scenario: Calculating the determinant of a 4x4 matrix
   Given the following 4x4 matrix A:
   | -2 | -8 | 3 | 5 |
   | -3 | 1 | 7 | 3 |
   | 1 | 2 | -9 | 6 |
   | -6 | 7 | 7 | -9 |
   Then cofactor(A, 0, 0) = 690
   And cofactor(A, 0, 1) = 447
   And cofactor(A, 0, 2) = 210
   And cofactor(A, 0, 3) = 51
   And determinant(A) = -4071
 */
TEST(MatrixTests, DetOf4x4)
{
    const auto data = std::vector<float>{
    -2,-8, 3, 5,
    -3, 1, 7, 3,
     1, 2,-9, 6,
    -6, 7, 7,-9 };
	
    auto a = Matrix(4, data);
    EXPECT_EQ(a.cofactor(0, 0), 690);
    EXPECT_EQ(a.cofactor(0, 1), 447);
    EXPECT_EQ(a.cofactor(0, 2), 210);
    EXPECT_EQ(a.cofactor(0, 3), 51);
    EXPECT_EQ(a.determinant(), -4071);
}



