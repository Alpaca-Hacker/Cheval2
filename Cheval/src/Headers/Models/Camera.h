#pragma once
#include "../DataStructures/Matrix.h"

class Camera
{
public:
	Camera(int h_size, int v_size, float fov)
	: h_size_(h_size)
	, v_size_(v_size)
	, fov_ (fov)
	{
		calculate_pixel_size();
	}

	int h_size() const { return h_size_; }
	int v_size() const { return v_size_; }
	float pixel_size() const { return pixel_size_; };
	float fov() const { return  fov_; }
	
	Matrix transform() const { return transform_; }
	Matrix& transform()  { return transform_; }

private:
	int h_size_{};
	int v_size_{};
	float fov_{};
	float half_width_{};
	float half_height_{};
	float pixel_size_{};
	Matrix transform_ = Matrix::identity();

	void calculate_pixel_size();
};

