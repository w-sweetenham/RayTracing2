#include "Object.h"

Object::Object(const TSphere& s, Material* material): material(material) {
    shape = new TSphere(s);
}

Object::Object(const Cube& c, Material* material): material(material) {
    shape = new Cube(c);
}

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