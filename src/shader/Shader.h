#ifndef SHADER_H_
#define SHADER_H_

#include <math.h>

#include "src/basicConstructs/Colour.h"
#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/object/Intersection.h"
#include "src/world/World.h"

class Shader {
    public:
    virtual Colour illumination(const IntersectionSpec& intSpec, const Ray& ray) const = 0;
    Colour getColour(const Ray& ray, const World& world) const;
};

class PhongShader : public Shader {
    public:
    Colour illumination(const IntersectionSpec& intSpec, const Ray& ray) const;
};

#endif