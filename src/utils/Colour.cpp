#include "Colour.h"

Colour::Colour(float red, float green, float blue) {
    rgb[0] = red;
    rgb[1] = green;
    rgb[2] = blue;
}

Colour::Colour(const Colour &other) {
    rgb[0] = other.rgb[0];
    rgb[1] = other.rgb[1];
    rgb[2] = other.rgb[2];
}

bool Colour::roughlyEqual(const Colour& other) const {
    return ::roughlyEqual(rgb[0], other.rgb[0]) && ::roughlyEqual(rgb[1], other.rgb[1]) && ::roughlyEqual(rgb[2], other.rgb[2]);
}

const Colour& Colour::operator=(const Colour& other) {
    for(int i=0; i<3; i++) {
        rgb[i] = other.rgb[i];
    }
    return *this;
}

float Colour::getRed() const {
    return rgb[0];
}

float Colour::getGreen() const {
    return rgb[1];
}

float Colour::getBlue() const {
    return rgb[2];
}

Colour Colour::operator+(const Colour &other) const {
    return Colour(rgb[0] + other.rgb[0], rgb[1] + other.rgb[1], rgb[2] + other.rgb[2]);
}

Colour Colour::operator-(const Colour &other) const {
    return Colour(rgb[0] - other.rgb[0], rgb[1] - other.rgb[1], rgb[2] - other.rgb[2]);
}

Colour Colour::operator*(const Colour &other) const {
    return Colour(rgb[0] * other.rgb[0], rgb[1] * other.rgb[1], rgb[2] * other.rgb[2]);
}

Colour Colour::operator*(float scalar) const {
    return Colour(rgb[0] * scalar, rgb[1] * scalar, rgb[2] * scalar);
}

Colour Colour::operator/(float scalar) const {
    return Colour(rgb[0] / scalar, rgb[1] / scalar, rgb[2] / scalar);
}

void Colour::operator+=(const Colour &other) {
    rgb[0] += other.rgb[0];
    rgb[1] += other.rgb[1];
    rgb[2] += other.rgb[2];
}

void Colour::operator-=(const Colour &other) {
    rgb[0] -= other.rgb[0];
    rgb[1] -= other.rgb[1];
    rgb[2] -= other.rgb[2];
}

void Colour::operator*=(float scalar) {
    rgb[0] *= scalar;
    rgb[1] *= scalar;
    rgb[2] *= scalar;
}

void Colour::operator/=(float scalar) {
    rgb[0] /= scalar;
    rgb[1] /= scalar;
    rgb[2] /= scalar;
}