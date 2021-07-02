#include "src/basicConstructs/Colour.h"

struct Material {
    float ambient;
    float diffuse;
    float specular;
    Colour colour;
    Material(float ambient, float diffuse, float specular, const Colour& colour);
};