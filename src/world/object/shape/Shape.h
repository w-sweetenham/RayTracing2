#ifndef SHAPE_H_
#define SHAPE_H_

#include <math.h>

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"
#include "src/world/object/Intersection.h"

class Shape {
    public:
    virtual bool intersection(const Ray& ray, IntersectionSet& intSet, const Object* objPtr) const = 0;
    virtual Vec getNorm(const Point& point) const = 0;
    virtual Shape* clone() const = 0;
};

#endif