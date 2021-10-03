#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "src/world/object/Object.h"
#include "src/world/lightSource/PointLight.h"
#include "src/world/object/Intersection.h"
#include "src/world/object/shape/TSphere.h"
#include "src/world/object/shape/Cube.h"
#include "src/world/object/material/Material.h"

class IndexOutOfBounds: public std::exception {
    public:
    virtual const char* what() const throw() {
        return "Index out of bounds";
    }
};

class World {
    private:
    std::vector<Object> objects;
    std::vector<Material> materials;
    PointLight light;
    public:
    bool isShadowed(const Point& point) const;
    World(const PointLight& light);
    PointLight getPointLight() const;
    void addObject(const TSphere& obj, const basicMaterial& material);
    void addObject(const Cube& obj, const basicMaterial& material);
    const Object* getObject(int index) const;
    int getNumObjects() const;
    IntersectionSpec getIntersection(const Ray& ray) const;
};

#endif