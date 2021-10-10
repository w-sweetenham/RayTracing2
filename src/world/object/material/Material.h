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
    virtual Colour getColour(const Point2D& materialPoint) const = 0;
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
    Colour getColour(const Point2D& materialPoint) const;
    Material* clone() const;
};

class Pattern {
    public:
    virtual Colour getColour(float x, float y) const = 0;
    virtual Pattern* clone() const = 0;
};

class CheckerPattern : public Pattern {
    private:
    Colour c1;
    Colour c2;
    public:
    CheckerPattern(const Colour& c1, const Colour& c2);
    CheckerPattern(const CheckerPattern& other);
    virtual Colour getColour(float x, float y) const;
    virtual Pattern* clone() const;
};

class PatternMaterial : public Material {
    private:
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float refractiveIndex;
    float reflectivity;
    float transparency;
    Pattern* pattern;
    public:
    PatternMaterial(float ambient, float diffuse, float specular, float shininess, const Pattern& pattern, float refractiveIndex, float reflectivity, float transparency);
    PatternMaterial(const PatternMaterial& other);
    void getSurfaceOpticParams(float& ambient, float& diffuse, float& specular, float& shininess, const Point& materialPoint) const;
    float getRefractiveIndex() const;
    float getReflectivity() const;
    float getTransparency() const;
    Colour getColour(const Point2D& materialPoint) const;
    Material* clone() const;
};

#endif