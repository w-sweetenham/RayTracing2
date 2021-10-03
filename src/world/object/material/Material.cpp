#include "Material.h"

basicMaterial::basicMaterial(float ambient, float diffuse, float specular, float shininess, const Colour& colour): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour), refractiveIndex(1), reflectivity(0), transparency(0) {}

basicMaterial::basicMaterial(float ambient, float diffuse, float specular, float shininess, const Colour& colour, float refractiveIndex, float reflectivity, float transparency): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour), refractiveIndex(refractiveIndex), reflectivity(reflectivity), transparency(transparency) {}

void basicMaterial::getSurfaceOpticParams(float& ambient, float& diffuse, float& specular, float& shininess, const Point& materialPoint) const {
    ambient = this->ambient;
    diffuse = this->diffuse;
    specular = this->specular;
    shininess = this->shininess;
}

Colour basicMaterial::getColour(const Point& materialPoint) const {
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