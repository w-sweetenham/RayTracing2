#include "Intersection.h"

Intersection::Intersection(float t, Object* objPtr): t(t), objPtr(objPtr) {}
    
float Intersection::getT() const {
    return t;
}
    
Object* Intersection::getObj() const {
    return objPtr;
}

bool Intersection::operator<(const Intersection& other) const{
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

bool IntersectionSet::getHit(Intersection& intersection) const {
    if(posIntersections.size() == 0) {
        return false;
    }

    intersection = *std::min_element(posIntersections.begin(), posIntersections.end());

    return true;
}