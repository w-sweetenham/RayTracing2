#include "PointLight.h"

PointLight::PointLight(const Point& origin, const Colour& intensity): origin(origin), intensity(intensity) {}

Point PointLight::getOrigin() const {
    return origin;
}

Colour PointLight::getIntensity() const {
    return intensity;
}