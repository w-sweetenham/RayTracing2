#include "Material.h"

basicMaterial::basicMaterial(float ambient, float diffuse, float specular, float shininess, const Colour& colour): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour), refractiveIndex(1), reflectivity(0), transparency(0) {}

basicMaterial::basicMaterial(float ambient, float diffuse, float specular, float shininess, const Colour& colour, float refractiveIndex, float reflectivity, float transparency): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour), refractiveIndex(refractiveIndex), reflectivity(reflectivity), transparency(transparency) {}

void basicMaterial::getSurfaceOpticParams(float& ambient, float& diffuse, float& specular, float& shininess, const Point& materialPoint) const {
    ambient = this->ambient;
    diffuse = this->diffuse;
    specular = this->specular;
    shininess = this->shininess;
}

Colour basicMaterial::getColour(const Point2D& materialPoint) const {
    return colour;
}

float basicMaterial::getRefractiveIndex() const {
    return refractiveIndex;
}
    
float basicMaterial::getReflectivity() const {
    return reflectivity;
}
    
float basicMaterial::getTransparency() const {
    return transparency;
}

Material* basicMaterial::clone() const {
    return new basicMaterial(*this);
}

CheckerPattern::CheckerPattern(const Colour& c1, const Colour& c2): c1(c1), c2(c2) {}

CheckerPattern::CheckerPattern(const CheckerPattern& other): c1(other.c1), c2(other.c2) {}

Colour CheckerPattern::getColour(float x, float y) const {
    bool xBool;
    bool yBool;

    if(x >= 0) {
        xBool = ((int)x)%2 == 0;
    } else {
        xBool = ((int)x)%2 != 0;
    }

    if(y >= 0) {
        yBool = ((int)y)%2 == 0;
    } else {
        yBool = ((int)y)%2 != 0;
    }

    if((xBool && yBool) || (!xBool && !yBool)) {
        return c1;
    }
    return c2;
}
    
Pattern* CheckerPattern::clone() const {
    return new CheckerPattern(*this);
}
    
PatternMaterial::PatternMaterial(float ambient, float diffuse, float specular, float shininess, const Pattern& pattern, float refractiveIndex, float reflectivity, float transparency): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), refractiveIndex(refractiveIndex), reflectivity(reflectivity), transparency(transparency) {
    this->pattern = pattern.clone();
}

PatternMaterial::PatternMaterial(const PatternMaterial& other): ambient(other.ambient), diffuse(other.diffuse), specular(other.specular), shininess(other.shininess), refractiveIndex(other.refractiveIndex), reflectivity(other.reflectivity), transparency(other.transparency) {
    pattern = other.pattern->clone();
}
    
void PatternMaterial::getSurfaceOpticParams(float& ambient, float& diffuse, float& specular, float& shininess, const Point& materialPoint) const {
    ambient = this->ambient;
    diffuse = this->diffuse;
    specular = this->specular;
    shininess = this->shininess;
}
    
float PatternMaterial::getRefractiveIndex() const {
    return refractiveIndex;
}
    
float PatternMaterial::getReflectivity() const {
    return reflectivity;
}
    
float PatternMaterial::getTransparency() const {
    return transparency;
}
    
Colour PatternMaterial::getColour(const Point2D& materialPoint) const {
    return pattern->getColour(materialPoint.x, materialPoint.y);
}
    
Material* PatternMaterial::clone() const {
    return new PatternMaterial(*this);
}