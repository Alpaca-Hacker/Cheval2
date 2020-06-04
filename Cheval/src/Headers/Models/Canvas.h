#pragma once
#include <cstdint>

#include "Colour.h"

class Canvas
{
public:
	Canvas(int height, int width);
	~Canvas();
	int write_file(char const* filename) const;
	void write_pixel(int x, int y, Colour const& colour) const;
	Colour pixel_at(int x, int y) const;

private:
	int height_ = 0;
	int width_ = 0;
	Colour* screen_;
};

