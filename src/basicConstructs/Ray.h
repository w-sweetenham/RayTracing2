#ifndef RAY_H_
#define RAY_H_

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"

class Matrix;
class Vec;
class Point;

class Ray {
    private:
    Point origin;
    Vec direction;
    public:
    Ray(const Point& origin, const Vec& direction);
    Point getOrigin() const;
    Vec getDirection() const;
    bool roughlyEqual(const Ray& other) const;
    Point getPosition(float t) const;
    Ray transform(const Matrix& mat) const;
    Ray& transformInPlace(const Matrix& mat);
};

#endif