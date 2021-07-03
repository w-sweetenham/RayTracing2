#ifndef TSPHERE_H_
#define TSPHERE_H_

#include <math.h>

#include "src/world/object/shape/MatTransformShape.h"
#include "src/basicConstructs/Ray.h"
#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"

class Ray;
class Vec;
class Point;
class Matrix;

class TSphere : public MatTransformShape {
    public:
    TSphere();
    TSphere(const Matrix& transformMat);
    TSphere(const TSphere& other);
    bool intersection(const Ray& ray, float& t) const;
    Vec getNorm(const Point& point) const;
};

#endif