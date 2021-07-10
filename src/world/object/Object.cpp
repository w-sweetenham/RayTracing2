#include "Object.h"

Object::Object(Shape* shape, std::string materialName): shape(shape), materialName(materialName) {}

bool Object::intersect(const Ray& ray, float& t) const {
    return shape->intersection(ray, t);
}

std::string Object::getMaterialName() const {
    return materialName;
}

Shape* Object::getShape() const {
    return shape;
}