#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "src/basicConstructs/Colour.h"

class Material {
    private:
    float ambient;
    float diffuse;
    float specular;
    Colour colour;
    public:
    Material(float ambient, float diffuse, float specular, const Colour& colour);
    float getAmbient();
    float getDiffuse();
    float getSpecular();
    Colour getColour();
};

#endif