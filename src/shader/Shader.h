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
    Colour getColour(const Ray& ray, const World& world, int recursion = 0) const;
    Colour getReflectedColour(const Ray& ray, const IntersectionSpec& intSpec, const World& world, int recursion = 0) const;
    Colour getRefractedColour(const Ray& ray, const IntersectionSpec& intSpec, const World& world, int recursion = 0) const;
};



class PhongShader : public Shader {
    public:
    Colour illumination(const IntersectionSpec& intSpec, const Ray& ray) const;
};

float schlick(float theta, float n1, float n2);

#endif