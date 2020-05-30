#pragma once
#include <cstdint>

#include "Colour.h"

class Canvas
{
public:
	Canvas(int height, int width);
	~Canvas();
	int write_file(char const* filename) const;
	void write_pixel(uint32_t x, uint32_t y, Colour const& colour) const;
	Colour pixel_at(uint32_t x, uint32_t y) const;

private:
	int height_ = 0;
	int width_ = 0;
	Colour* screen_;
};

