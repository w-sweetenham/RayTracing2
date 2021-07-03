#include "Material.h"

Material::Material(float ambient, float diffuse, float specular, const Colour& colour): ambient(ambient), diffuse(diffuse), specular(specular), colour(colour) {}

float Material::getAmbient() {
    return ambient;
}

float Material::getDiffuse() {
    return diffuse;
}

float Material::getSpecular() {
    return specular;
}

Colour Material::getColour() {
    return colour;
}