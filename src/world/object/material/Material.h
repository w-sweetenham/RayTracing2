#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "src/basicConstructs/Colour.h"
#include "src/basicConstructs/Tuple.h"

class Material {
    public:
    virtual void getSurfaceOpticParams(float& ambient, float& diffuse, float& specular, float& shininess, const Point& materialPoint) const = 0;
    virtual float getRefractiveIndex() const = 0;
    virtual float getReflectivity() const = 0;
    virtual float getTransparency() const = 0;
    virtual Colour getColour(const Point& materialPoint) const = 0;
    virtual Material* clone() const = 0;
};

class basicMaterial : public Material {
    private:
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    Colour colour;
    float refractiveIndex;
    float reflectivity;
    float transparency;
    public:
    basicMaterial(float ambient, float diffuse, float specular, float shininess, const Colour& colour);
    basicMaterial(float ambient, float diffuse, float specular, float shininess, const Colour& colour, float refractiveIndex, float reflectivity, float transparency);
    void getSurfaceOpticParams(float& ambient, float& diffuse, float& specular, float& shininess, const Point& materialPoint) const;
    float getRefractiveIndex() const;
    float getReflectivity() const;
    float getTransparency() const;
    Colour getColour(const Point& materialPoint) const;
    Material* clone() const;
};

#endif