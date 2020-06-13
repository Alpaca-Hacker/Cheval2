#pragma once
#include "../Colour.h"
#include "../../DataStructures/Tuple.h"

class Light
{
public:
	Light(Tuple position, Colour intensity)
		: position_(position)
		, intensity_(intensity)
	{
	}
	Tuple position() const
	{
		return position_;
	}
	
	Colour intensity() const
	{
		return intensity_;
	}
	
private:
	Tuple position_;
	Colour intensity_;

};

inline Light Point_Light(Tuple position, Colour intensity)
{
	return {position, intensity};
}

