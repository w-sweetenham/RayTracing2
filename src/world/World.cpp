#include "World.h"

World::World(const PointLight& light): light(light) {}

bool World::isShadowed(const Point& point) const {
    Vec lightVec = light.getOrigin() - point;
    Ray lightRay(point, lightVec);
    IntersectionSet intersections;
    int prevCount = 0;
    for(int i=0; i<objects.size(); i++) {
        objects[i].intersect(lightRay, intersections);
        if(intersections.getNumPosIntersections() > prevCount) {
            prevCount = intersections.getNumPosIntersections();
            Intersection lastIntersection = intersections.getPosIntersection(prevCount-1);
            if(lastIntersection.getT() < 1 && lastIntersection.getObj()->material->getTransparency() < 0.001) {
                return true;
            }
        }
    }
    return false;
}

PointLight World::getPointLight() const {
    return light;
}

void World::addObject(const TSphere& s, const Material& material) {
    objects.push_back(Object(s, material));
}

void World::addObject(const Cube& c, const Material& material) {
    objects.push_back(Object(c, material));
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
    bool hit = intersections.getHit(i, obj1, obj2, NULL);
    if(hit == false) {
        return IntersectionSpec(false, Vec(0, 0, 0), Point(0, 0, 0), NULL, obj1, obj2, Vec(0, 0, 0), light.getIntensity(), false);
    }
    Point p = ray.getPosition(i.getT());
    Vec norm = i.getObj()->getNorm(p);
    Vec lightVec = light.getOrigin() - p;
    lightVec.normalize();
    Vec eyeVec = ray.getDirection() * -1.0;
    if(norm.dot(eyeVec) < 0) {
        norm *= -1.0;
    }
    norm.normalize();
    Point underPoint = p + norm*0.00001;
    Point overPoint = p - norm*0.00001;
    return IntersectionSpec(true, norm, p, i.getObj(), obj1, obj2, lightVec, light.getIntensity(), isShadowed(underPoint), overPoint, underPoint);
}

