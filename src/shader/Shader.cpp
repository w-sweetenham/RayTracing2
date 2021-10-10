#include "Shader.h"

Colour Shader::getColour(const Ray& ray, const World& world, int recursion) const {
    if(recursion < 0) {
        return Colour(0, 0, 0);
    }
    IntersectionSpec intSpec = world.getIntersection(ray);
    if(intSpec.hit) {
        Colour surfaceColour = illumination(intSpec, ray);
        Colour reflectedColour(0, 0, 0);
        Colour refractedColour(0, 0, 0);
        bool isTransparent = intSpec.hitObj->material->getTransparency() > 0.0001;
        bool isReflective = intSpec.hitObj->material->getReflectivity() > 0.0001;
        if(isTransparent) {
            refractedColour = getRefractedColour(ray, intSpec, world, recursion);
        }
        if(isReflective) {
            reflectedColour = getReflectedColour(ray, intSpec, world, recursion);
        }
        if(isTransparent && isReflective) {
            Vec eyeVec = ray.getDirection()*(-1.0);
            eyeVec.normalize();
            float theta;
            float dotProduct = eyeVec.dot(intSpec.norm);
            if(dotProduct > 0.99999) {
                theta = 0;
            } else {
                theta = acos(eyeVec.dot(intSpec.norm));
            }
            float n1;
            float n2;
            if(intSpec.obj1 == NULL) {
                n1 = 1.0;
            } else {
                n1 = intSpec.obj1->material->getRefractiveIndex();
            }
            if(intSpec.obj2 == NULL) {
                n2 = 1.0;
            } else {
                n2 = intSpec.obj2->material->getRefractiveIndex();
            }
            float reflectivity = schlick(theta, n1, n2);

            return surfaceColour + reflectedColour*reflectivity + refractedColour*(1-reflectivity);
        }
        return surfaceColour + reflectedColour + refractedColour;
    } else {
        return Colour(0, 0, 0);
    }
}

Colour Shader::getReflectedColour(const Ray& ray, const IntersectionSpec& intSpec, const World& world, int recursion) const {
    Vec reflectedVec = (ray.getDirection()*(-1.0)).reflect(intSpec.norm);
    Ray reflectedRay(intSpec.underPoint, reflectedVec);
    return getColour(reflectedRay, world, recursion-1)*intSpec.hitObj->material->getReflectivity();
}

Colour Shader::getRefractedColour(const Ray& ray, const IntersectionSpec& intSpec, const World& world, int recursion) const {
    bool isTIR;
    float n1, n2;
    if(intSpec.obj1 == NULL) {
        n1 = 1;
    } else {
        n1 = intSpec.obj1->material->getRefractiveIndex();
    }
    if(intSpec.obj2 == NULL) {
        n2 = 1.0;
    } else {
        n2 = intSpec.obj2->material->getRefractiveIndex();
    }
    Vec refractedVec = ray.getDirection().refract(intSpec.norm, n1, n2, isTIR);
    Ray refractedRay(intSpec.overPoint, refractedVec);

    if(isTIR) {
        return Colour(0, 0, 0);
    }

    return getColour(refractedRay, world, recursion-1)*intSpec.hitObj->material->getTransparency();
}

Colour PhongShader::illumination(const IntersectionSpec& intSpec, const Ray& ray) const {
    Vec reflectedVec = intSpec.lightVec.reflect(intSpec.norm);
    Vec eyeVec = ray.getDirection() * -1.0;
    eyeVec.normalize();
    float ambient, diffuse, specular, shininess;
    intSpec.hitObj->material->getSurfaceOpticParams(ambient, diffuse, specular, shininess, intSpec.point);
    if(intSpec.isShadowed) {
        return intSpec.lightIntensity * intSpec.hitObj->getColour(intSpec.point) * ambient;
    }
    float diffuseFactor;
    if(intSpec.lightVec.dot(intSpec.norm) >= 0) {
        diffuseFactor = diffuse * intSpec.lightVec.dot(intSpec.norm);
    } else {
        diffuseFactor = 0.0;
    }
    float specularFactor;
    if(reflectedVec.dot(eyeVec) >= 0.0) {
        specularFactor = pow(reflectedVec.dot(eyeVec), shininess);
    } else {
        specularFactor = 0.0;
    }
    specularFactor *= specular;
    Colour c = (intSpec.hitObj->getColour(intSpec.point) * intSpec.lightIntensity) * (ambient + diffuseFactor);
    c += intSpec.lightIntensity * specularFactor;
    
    return c;
}

float schlick(float theta, float n1, float n2) {
    if(n1 > n2 && (n1/n2) * sin(theta) > 1.0) {
        return 1.0;
    }
    float r0 = pow((n1 - n2)/(n1 + n2), 2);
    return r0 + (1-r0)*pow(1-cos(theta), 5);
}