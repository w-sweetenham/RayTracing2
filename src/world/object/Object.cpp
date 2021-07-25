#include "Object.h"

Object::Object(Shape* shape, Material* material): shape(shape), material(material) {}

void Object::intersect(const Ray& ray, IntersectionSet& intSet) const {
    shape->intersection(ray, intSet, this);
}

Vec Object::getNorm(const Point& point) const {
    return shape->getNorm(point);
}

Material* Object::getMaterial() const {
    return material;
}

Shape* Object::getShape() const {
    return shape;
}