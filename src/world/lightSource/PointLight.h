#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Colour.h"

class PointLight {
    private:
    Point origin;
    Colour intensity;
    public:
    PointLight(const Point& origin, const Colour& intensity);
    Point getOrigin() const;
    Colour getIntensity() const;
};

#endif