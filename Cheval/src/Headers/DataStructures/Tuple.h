#pragma once
class Tuple
{
public:
	Tuple();
	Tuple(float x, float y, float z, float w);

    bool is_point() const;
    bool is_vector() const;
    float magnitude() const;

	float X() const { return x_; }
    float Y() const { return y_; }
    float Z() const { return z_; }
    float W() const { return w_; }

    float& X() { return x_; }
    float& Y() { return y_; }
    float& Z() { return z_; }
    float& W() { return w_; }

    bool operator==(const Tuple& other);
    bool operator!=(const Tuple& other);
    bool operator==(Tuple& other);
    bool operator!=(Tuple& other);
	
	static Tuple reflect(const Tuple& in, const Tuple& normal);

	static Tuple normalize(const Tuple& v);

	static float dot(const Tuple& a, const Tuple& b);

	static Tuple cross(const Tuple& a, const Tuple& b);

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


#define APPLY_OPERATOR(a, b, op) { a.X() op b.X(), a.Y() op b.Y(), a.Z() op b.Z(), a.W() op b.W() }
inline Tuple operator+(Tuple const& a, Tuple const& b) { return APPLY_OPERATOR(a, b, +); }
inline Tuple operator-(Tuple const& a, Tuple const& b) { return APPLY_OPERATOR(a, b, -); }
inline Tuple operator*(Tuple const& a, Tuple const& b) { return APPLY_OPERATOR(a, b, *); }
#undef APPLY_OPERATOR

inline Tuple operator*(Tuple const& a, float b) { return { a.X() * b, a.Y() * b, a.Z() * b, a.W()}; }
inline Tuple operator/(Tuple const& a, float b) { return a * (1.f / b); }
inline Tuple operator-(Tuple const& t) { return { -t.X(), -t.Y(), -t.Z(), t.W() }; }
bool operator==(const Tuple& first, const Tuple& other);
bool operator!=(const Tuple& first, const Tuple& other);
