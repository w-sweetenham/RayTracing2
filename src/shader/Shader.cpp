#include "Shader.h"

Colour Shader::getColour(const Ray& ray, const World& world) const {
    IntersectionSpec intSpec = world.getIntersection(ray);
    return illumination(intSpec, ray);
}

Colour PhongShader::illumination(const IntersectionSpec& intSpec, const Ray& ray) const {
    Vec reflectedVec = intSpec.lightVec.reflect(intSpec.norm);
    Vec eyeVec = ray.getDirection() * -1.0;
    eyeVec.normalize();
    float ambientFactor = intSpec.obj2->getMaterial()->getAmbient();
    float diffuseFactor = intSpec.obj2->getMaterial()->getDiffuse() * intSpec.lightVec.dot(intSpec.norm);
    float specularfactor = pow(reflectedVec.dot(eyeVec), intSpec.obj2->getMaterial()->getShininess());
    specularfactor *= intSpec.obj2->getMaterial()->getSpecular();
    Colour c = (intSpec.obj2->getMaterial()->getColour() * intSpec.lightIntensity) * (ambientFactor + diffuseFactor);
    c += intSpec.lightIntensity * specularfactor;
    return c;
}