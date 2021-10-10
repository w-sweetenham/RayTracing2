#include "Object.h"

Object::Object(const TSphere& s, const Material& material): material(material.clone()) {
    shape = new TSphere(s);
}

Object::Object(const Cube& c, const Material& material): material(material.clone()) {
    shape = new Cube(c);
}

Object::Object(const Object& other) {
    material = other.material->clone();
    shape = other.shape->clone();
}

Object::~Object() {
    delete material;
    delete shape;
}

void Object::intersect(const Ray& ray, IntersectionSet& intSet) const {
    shape->intersection(ray, intSet, this);
}

Vec Object::getNorm(const Point& point) const {
    return shape->getNorm(point);
}

Shape* Object::getShape() const {
    return shape;
}

Colour Object::getColour(const Point& point) const {
    return material->getColour(shape->getTexelPoint(point));
}