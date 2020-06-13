#include "../Headers/Models/Camera.h"

void Camera::calculate_pixel_size()
{
	const float half_view = tanf(fov_ / 2.0f);
	const float aspect = static_cast<float>(h_size_) / static_cast<float>(v_size_);

	if (aspect >= 1) {
		half_width_ = half_view;
		half_height_ = half_view / aspect;
	}
	else
	{
		half_width_ = half_view * aspect;
		half_height_ = half_view;
	}
	
	pixel_size_ = half_width_ * 2.0f / static_cast<float>(h_size_);
}
