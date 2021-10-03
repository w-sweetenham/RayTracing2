#ifndef CUBE_H_
#define CUBE_H_

#include <math.h>
#include <algorithm>

#include "src/world/object/shape/MatTransformShape.h"
#include "src/world/object/Intersection.h"
#include "src/basicConstructs/Ray.h"
#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"
#include "src/utils/Utils.h"

class Ray;
class Vec;
class Point;
class Matrix;

class Cube : public MatTransformShape {
    public:
    Cube();
    Cube(const Matrix& transformMat);
    Cube(const Cube& other);
    bool intersection(const Ray& ray, IntersectionSet& intSet, const Object* objPtr) const;
    Vec getNorm(const Point& point) const;
    virtual Shape* clone() const;
};

#endif