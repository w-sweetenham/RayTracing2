#include "Intersection.h"

Intersection::Intersection(float t, const Object* objPtr): t(t), objPtr(objPtr) {}

Intersection::Intersection(const Intersection& other): t(other.t), objPtr(other.objPtr) {}
    
float Intersection::getT() const {
    return t;
}
    
const Object* Intersection::getObj() const {
    return objPtr;
}

bool Intersection::operator<(const Intersection& other) const {
    if(this->t < other.t) {
        return true;
    } else {
        return false;
    }
}


void IntersectionSet::addIntersection(const Intersection& intersection) {
    if(intersection.getT() >= 0.0) {
        posIntersections.push_back(intersection);
    } else {
        negIntersections.push_back(intersection);
    }
    return;
}

int IntersectionSet::getNumNegIntersections() const {
    return negIntersections.size();
}

int IntersectionSet::getNumPosIntersections() const {
    return posIntersections.size();
}

Intersection IntersectionSet::getPosIntersection(int index) const {
    if(index >= posIntersections.size() || index < 0) {
        throw BadIndex();
    } else {
        return posIntersections[index];
    }
}

Intersection IntersectionSet::getNegIntersection(int index) const {
    if(index >= negIntersections.size() || index < 0) {
        throw BadIndex();
    } else {
        return negIntersections[index];
    }
}

bool IntersectionSet::getHit(Intersection& intersection, const Object*& prevObj, const Object*& nextObj, const Object* const defaultObj) {
    if(posIntersections.size() == 0) {
        return false;
    }
    
    std::sort(posIntersections.begin(), posIntersections.end());
    std::sort(negIntersections.begin(), negIntersections.end());
    intersection = posIntersections[0];

    
    std::vector<const Object*> containers;
    std::vector<const Object*>::iterator objPtr;

    for(int i=0; i<negIntersections.size(); i++) {
        objPtr = std::find(containers.begin(), containers.end(), negIntersections[i].getObj());
        if(objPtr == containers.end()) {//containers doesn't contain the object of the current intersection
            containers.push_back(negIntersections[i].getObj());
        } else {
            containers.erase(objPtr);
        }
    }

    if(containers.size() == 0) {
        prevObj = defaultObj;
    } else {
        prevObj = containers[containers.size() - 1];
    }

    objPtr = std::find(containers.begin(), containers.end(), posIntersections[0].getObj());
    if(objPtr == containers.end()) {//containers doesn't contain the object of the current intersection
        containers.push_back(posIntersections[0].getObj());
    } else {
        containers.erase(objPtr);
    }

    if(containers.size() == 0) {
        nextObj = defaultObj;
    } else {
        nextObj = containers[containers.size() - 1];
    }
    return true;
}

IntersectionSpec::IntersectionSpec(bool hit, 
                    const Vec& norm, 
                    const Point& point, 
                    float ambient, 
                    float diffuse, 
                    float specular, 
                    float shininess,
                    float n1,
                    float n2,
                    float reflectivity,
                    float transparency,
                    const Colour& colour, 
                    const Vec& lightVec, 
                    const Colour& intensity, 
                    bool isShadowed): hit(hit),
                                      norm(norm),
                                      point(point),
                                      ambient(ambient),
                                      diffuse(diffuse),
                                      specular(specular),
                                      shininess(shininess),
                                      n1(n1),
                                      n2(n2),
                                      reflectivity(reflectivity),
                                      transparency(transparency),
                                      colour(colour),
                                      lightVec(lightVec),
                                      lightIntensity(intensity),
                                      isShadowed(isShadowed) {}