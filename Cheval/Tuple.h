#pragma once
class Tuple
{
public:
	Tuple();
	Tuple(float x, float y, float z, float w);

	bool is_point() const
	{
        return (w_ == 1.0f);
	}

	bool is_vector() const
	{
		return (w_ == 0.0f);
	}

	float X() const { return x_; }
    float Y() const { return y_; }
    float Z() const { return z_; }
    float W() const { return w_; }

    float& X() { return x_; }
    float& Y() { return y_; }
    float& Z() { return z_; }
    float& W() { return w_; }

	

private:
    float x_;
    float y_;
    float z_;
    float w_;
};

inline Tuple Point(float x, float y, float z)
{
	return { x, y, z, 1.0f };
}

inline Tuple Vector(float x, float y, float z)
{
	return { x, y, z, 0.0f };
}

