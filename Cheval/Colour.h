#pragma once

#include "Tuple.h"

class Colour : public Tuple
{
public:
    Colour(Tuple const& t) : Tuple(t.X(), t.Y(), t.Z(), 0.0f) {}
    Colour(float r, float g, float b) : Tuple(r, g, b, 0.0f) {}

    float R() const { return this->X(); }
    float B() const { return this->Z(); }

    static Colour const& White() { static Colour c(1.f, 1.f, 1.f); return c; }
    static Colour const& Black() { static Colour c(0.f, 0.f, 0.f); return c; }
    static Colour const& Red() { static Colour c(1.f, 0.f, 0.f); return c; }
    static Colour const& Green() { static Colour c(0.f, 1.f, 0.f); return c; }
    static Colour const& Blue() { static Colour c(0.f, 0.f, 1.f); return c; }
    static Colour const& Yellow() { static Colour c(1.f, 1.f, 0.f); return c; }
};

