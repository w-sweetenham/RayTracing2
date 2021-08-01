#include "Shader.h"

Colour Shader::getColour(const Ray& ray, const World& world) const {
    IntersectionSpec intSpec = world.getIntersection(ray);
    if(intSpec.hit) {
        return illumination(intSpec, ray);
    } else {
        return Colour(0, 0, 0);
    }
}

Colour PhongShader::illumination(const IntersectionSpec& intSpec, const Ray& ray) const {
    Vec reflectedVec = intSpec.lightVec.reflect(intSpec.norm);
    Vec eyeVec = ray.getDirection() * -1.0;
    eyeVec.normalize();
    float ambientFactor = intSpec.hitObj->getMaterial()->getAmbient();
    if(intSpec.isShadowed) {
        return intSpec.lightIntensity * intSpec.hitObj->getMaterial()->getColour() * ambientFactor;
    }
    float diffuseFactor;
    if(intSpec.lightVec.dot(intSpec.norm) >= 0) {
        diffuseFactor = intSpec.hitObj->getMaterial()->getDiffuse() * intSpec.lightVec.dot(intSpec.norm);
    } else {
        diffuseFactor = 0.0;
    }
    float specularFactor;
    if(reflectedVec.dot(eyeVec) >= 0.0) {
        specularFactor = pow(reflectedVec.dot(eyeVec), intSpec.hitObj->getMaterial()->getShininess());
    } else {
        specularFactor = 0.0;
    }
    specularFactor *= intSpec.hitObj->getMaterial()->getSpecular();
    Colour c = (intSpec.hitObj->getMaterial()->getColour() * intSpec.lightIntensity) * (ambientFactor + diffuseFactor);
    c += intSpec.lightIntensity * specularFactor;
    
    return c;
}