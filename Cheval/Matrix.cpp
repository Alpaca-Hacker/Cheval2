#include <functional>

#include "Matrix.h"
#include "Tuple.h"
#include "Utils.h"

std::function<bool(float, float)>equals_comparator = [](float a, float b)
{
	return Equals(a, b);
};

Matrix Matrix::transpose() const
{
	auto m = Matrix(4, data_);
	auto result = Matrix(4, std::vector<float>{
		m(0, 0), m(1, 0), m(2, 0), m(3, 0),
		m(0, 1), m(1, 1), m(2, 1), m(3, 1),
		m(0, 2), m(1, 2), m(2, 2), m(3, 2),
		m(0, 3), m(1, 3), m(2, 3), m(3, 3)
	});
	return result;
}

float Matrix::determinant() const
{
	auto M = Matrix(size_, data_);
	auto result = 0.0f;
	if (size_ == 2)
	{
		result = data_[0] * data_[3] - data_[1] * data_[2];
	}
	else
	{
		for (unsigned i = 0; i < size_; i++)
		{
			result += M(0, i) * cofactor(0, i);
		}
	}
	return result;
}

Matrix Matrix::submatrix(unsigned row, unsigned col) const
{
	auto M = Matrix(size_, data_);
	auto NewMat = Matrix(size_ - 1);

	auto newRow = 0;
	auto newCol = 0;
	for (unsigned i = 0; i < M.size(); i++)
	{
		if (i == col)
		{
			continue;
		}

		for (unsigned j = 0; j < M.size(); j++)
		{
			if (j == row)
			{
				continue;
			}

			NewMat(newRow, newCol) = M(j, i);
			newRow++;
		}

		newCol++;
		newRow = 0;
	}

	return NewMat;
}

float Matrix::minor(unsigned row, unsigned col) const
{
	auto sub = submatrix(row, col);
	auto det = sub.determinant();
	return det;
}

float Matrix::cofactor(unsigned row, unsigned col) const
{
	auto result = minor(row, col);
	if ((row + col) % 2 != 0)
	{
		result = -result;
	}

	return result;
}


bool Matrix::operator==(const Matrix& m) const
{
	if (size_ != m.size())
	{
		return false;
	}
	
	return std::equal(data_.begin(), data_.end(), 
		m.data_.begin(), equals_comparator);
}

bool Matrix::operator!=(const Matrix& m) const
{
	return !(this->operator==(m));
}


unsigned Matrix::size() const
{
	return size_;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.size() != rhs.size() && lhs.size() != 4)
	{
		return { lhs }; //Todo error here
	}
	auto result = Matrix(4);
	for (int row =0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			result(row, col) = 
				lhs(row, 0) * rhs(0, col) +
				lhs(row, 1) * rhs(1, col) +
				lhs(row, 2) * rhs(2, col) +
				lhs(row, 3) * rhs(3, col);
		}
	}
	return result;
}

float calculate_elem(const Matrix& lhs, const Tuple& rhs, int row)
{
	return 
		lhs(row, 0) * rhs.X() +
		lhs(row, 1) * rhs.Y() +
		lhs(row, 2) * rhs.Z() +
		lhs(row, 3) * rhs.W();
}

Tuple operator*(const Matrix& mat, const Tuple& tup)
{
	if (mat.size() != 4)
	{
		return { tup }; //Todo error here
	}

	auto x = calculate_elem(mat, tup, 0);
	auto y = calculate_elem(mat, tup, 1);
	auto z = calculate_elem(mat, tup, 2);
	auto w = calculate_elem(mat, tup, 3);
		
	return { x,y,z,w };
}

Tuple operator*(const Tuple& tup, const Matrix& mat)
{
	return { mat * tup};
}