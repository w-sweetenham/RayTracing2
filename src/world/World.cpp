#include "World.h"

World::World(const PointLight& light): light(light) {}

PointLight World::getPointLight() const {
    return light;
}

void World::addMaterial(const Material& material) {
    materials.push_back(material);
}

int World::getNumMaterials() const {
    return materials.size();
}

void World::addObject(const TSphere& s, int matIndex) {
    if(matIndex >= materials.size()) {
        throw IndexOutOfBounds();
    } else {
        objects.push_back(Object(s, &materials[matIndex]));
    }
}

const Object* World::getObject(int index) const {
    if(index >= objects.size()) {
        throw IndexOutOfBounds();
    } else {
        return &objects[index];
    }
}

int World::getNumObjects() const {
    return objects.size();
}

IntersectionSpec World::getIntersection(const Ray& ray) const {
    IntersectionSet intersections;
    for(int i=0; i<objects.size(); i++) {
        objects[i].intersect(ray, intersections);
    }
    Intersection i(0, NULL);
    const Object* obj1;
    const Object* obj2;
    intersections.getHit(i, obj1, obj2, NULL);
    Point p = ray.getPosition(i.getT());
    Vec norm = i.getObj()->getNorm(p);
    Vec lightVec = light.getOrigin() - p;
    lightVec.normalize();
    Vec eyeVec = ray.getDirection() * -1.0;
    if(norm.dot(eyeVec) < 0) {
        norm *= -1.0;
    }
    return IntersectionSpec(norm, p, obj1, obj2, lightVec, light.getIntensity());
}

