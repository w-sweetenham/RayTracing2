#ifndef OBJECT_H_
#define OBJECT_H_

#include "src/basicConstructs/Ray.h"
#include "src/world/object/shape/Shape.h"
#include "src/world/object/shape/TSphere.h"
#include "src/world/object/shape/Cube.h"
#include "src/world/object/material/Material.h"
#include "src/world/object/Intersection.h"

class Object {
    private:
    Shape* shape;
    public:
    const Material* material;
    Object(const TSphere& s, const basicMaterial& material);
    Object(const Cube& s, const basicMaterial& material);
    Object(const Object& other);
    ~Object();
    void intersect(const Ray& ray, IntersectionSet& intSet) const;
    Vec getNorm(const Point& point) const;
    Shape* getShape() const;
};

#endif