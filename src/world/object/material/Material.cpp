#include "Material.h"

Material::Material(float ambient, float diffuse, float specular, float shininess, const Colour& colour): ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), colour(colour) {}

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