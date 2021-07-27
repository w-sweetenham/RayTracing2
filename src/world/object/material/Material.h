#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "src/basicConstructs/Colour.h"

class Material {
    private:
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    Colour colour;
    public:
    Material(float ambient, float diffuse, float specular, float shininess, const Colour& colour);
    float getAmbient() const;
    float getDiffuse() const;
    float getSpecular() const;
    float getShininess() const;
    Colour getColour() const;
};

#endif