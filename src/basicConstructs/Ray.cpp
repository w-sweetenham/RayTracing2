#include "Ray.h"

Ray::Ray(const Point& origin, const Vec& direction): origin(origin), direction(direction) {}

Point Ray::getOrigin() const {
    return origin;
}

Vec Ray::getDirection() const {
    return direction;
}

bool Ray::roughlyEqual(const Ray& other) const {
    return origin.roughlyEqual(other.origin) && direction.roughlyEqual(other.direction);
}

Point Ray::getPosition(float t) const {
    return origin + (direction*t);
}

Ray Ray::transform(const Matrix& mat) const {
    return Ray(mat*origin, mat*direction);
}

Ray& Ray::transformInPlace(const Matrix& mat) {
    origin = mat*origin;
    direction = mat*direction;
    return *this;
}