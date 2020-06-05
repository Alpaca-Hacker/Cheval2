#pragma once
#include <utility>
#include <vector>

#include "Tuple.h"

class Matrix {
public:
    Matrix(unsigned size);
    Matrix(unsigned size, std::vector<float> data);

	~Matrix();
	
    float& operator() (unsigned row, unsigned col);        
    float operator() (unsigned row, unsigned col) const;
    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;

	Matrix transpose() const;
    float determinant() const;
    Matrix submatrix(unsigned row, unsigned col) const;
    float minor(unsigned row, unsigned col) const;
	float cofactor(unsigned row, unsigned col) const;
    Matrix inverse();

    bool isInvertable()
    {
        return determinant() != 0;
    }

    static auto identity() -> Matrix;

    unsigned size() const;

private:
    unsigned size_ = 0;
    std::vector<float> data_;
	
};

inline Matrix Matrix::inverse()
{
	if (!isInvertable())
	{
        return *this; // TODO: Throw error!
	}
    auto newMatrix = Matrix(size_);
	const auto det = determinant();
	
    for (unsigned row = 0; row < size_; row++)
    {
        for (unsigned column = 0; column < size_; column++)
        {
            auto cof = cofactor(row, column);
            newMatrix(column, row) = cof / det;
        }
    }
    return newMatrix;
}


inline
Matrix::Matrix(unsigned size)
	:size_(size)
    , data_(std::vector<float>(size_* size_))
{
    for (unsigned i = 0; i < size_ * size_; ++i)
    {
        data_[i] = 0.0f;
    }
}

inline
Matrix::Matrix(unsigned size, std::vector<float> data)
    :size_(size)
    , data_(std::move(data))
{

}

inline
Matrix::~Matrix()
= default;

inline
float& Matrix::operator() (unsigned row, unsigned col)
{
    return data_[size_ * row + col];
}

inline
float Matrix::operator() (unsigned row, unsigned col) const
{
    if (row >= size_ || col >= size_) {
        return 0.0f;
    }
    return data_[size_ * row + col];
}

inline auto Matrix::identity() -> Matrix
{
    return Matrix(4, std::vector<float>{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1});
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Tuple operator*(const Matrix& mat, const Tuple& tup);
Tuple operator*(const Tuple& tup, const Matrix& mat);



