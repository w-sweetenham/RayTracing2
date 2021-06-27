#ifndef COLOUR_H_
#define COLOUR_H_
#include <iostream>

class Colour {
    private:
    float rgb[3];
    public:
    Colour(float red, float green, float blue);
    Colour(const Colour& other);
    const Colour& operator=(const Colour& other);

    float getRed() const;
    float getGreen() const;
    float getBlue() const;

    bool roughlyEqual(const Colour& other);

    Colour operator+(const Colour& other) const;
    Colour operator-(const Colour& other) const;
    Colour operator*(const Colour& other) const;
    Colour operator*(float scalar) const;
    Colour operator/(float scalar) const;

    void operator+=(const Colour& other);
    void operator-=(const Colour& other);
    void operator*=(float scalar);
    void operator/=(float scalar);
};

#endif