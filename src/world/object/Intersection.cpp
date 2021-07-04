#include "Intersection.h"

Intersection::Intersection(float t, Object* objPtr): t(t), objPtr(objPtr) {}
    
float Intersection::getT() const {
    return t;
}
    
Object* Intersection::getObj() const {
    return objPtr;
}