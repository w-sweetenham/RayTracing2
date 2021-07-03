#ifndef SHAPE_H_
#define SHAPE_H_

#include <math.h>

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"

class Shape {
    public:
    virtual bool intersection(const Ray& ray, float& t) const = 0;
    virtual Vec getNorm(const Point& point) const = 0;
};

#endif