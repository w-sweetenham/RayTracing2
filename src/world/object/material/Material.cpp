#include "Material.h"

Material::Material(float ambient, float diffuse, float specular, float shininess, const Colour& colour): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour), refractiveIndex(1), reflectivity(0), transparency(0) {}

Material::Material(float ambient, float diffuse, float specular, float shininess, const Colour& colour, float refractiveIndex, float reflectivity, float transparency): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour), refractiveIndex(refractiveIndex), reflectivity(reflectivity), transparency(transparency) {}

float Material::getAmbient() const {
    return ambient;
}

float Material::getDiffuse() const {
    return diffuse;
}

float Material::getSpecular() const {
    return specular;
}

float Material::getShininess() const {
    return shininess;
}

Colour Material::getColour() const {
    return colour;
}

float Material::getRefractiveIndex() const {
    return refractiveIndex;
}
    
float Material::getReflectivity() const {
    return reflectivity;
}

float Material::getTransparency() const {
    return transparency;
}