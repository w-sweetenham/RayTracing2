#ifndef OBJECT_H_
#define OBJECT_H_

#include "src/basicConstructs/Ray.h"
#include "src/world/object/shape/Shape.h"
#include "src/world/object/material/Material.h"
#include "src/world/object/Intersection.h"

class Object {
    private:
    Shape* shape;
    std::string materialName;
    public:
    Object(Shape* shape, std::string materialName);
    bool intersect(const Ray& ray, IntersectionSet& intSet) const;
    Vec getNorm(const Point& point) const;
    std::string getMaterialName() const;
    Shape* getShape() const;
};

#endif