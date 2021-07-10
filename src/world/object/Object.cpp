#include "Object.h"

Object::Object(Shape* shape, std::string materialName): shape(shape), materialName(materialName) {}

bool Object::intersect(const Ray& ray, IntersectionSet& intSet) const {
    return shape->intersection(ray, intSet, this);
}

Vec Object::getNorm(const Point& point) const {
    return shape->getNorm(point);
}

std::string Object::getMaterialName() const {
    return materialName;
}

Shape* Object::getShape() const {
    return shape;
}