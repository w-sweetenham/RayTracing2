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
        return IntersectionSpec(false, Vec(0, 0, 0), Point(0, 0, 0), 0, 0, 0, 0, 0, 0, 0, 0, Colour(0, 0, 0), Vec(0, 0, 0), Colour(0, 0, 0), false);
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
    float ambient, diffuse, specular, shininess;
    const Object* hitObj = i.getObj();
    hitObj->material->getSurfaceOpticParams(ambient, diffuse, specular, shininess, p);
    float n1, n2;
    if(obj1 == NULL) {
        n1 = 1;
    } else {
        n1 = obj1->material->getRefractiveIndex();
    }
    if(obj2 == NULL) {
        n2 = 1.0;
    } else {
        n2 = obj2->material->getRefractiveIndex();
    }
    return IntersectionSpec(true, 
                            norm, 
                            p, 
                            ambient, 
                            diffuse, 
                            specular, 
                            shininess, 
                            n1, 
                            n2, 
                            hitObj->material->getReflectivity(), 
                            hitObj->material->getTransparency(),
                            hitObj->getColour(p),
                            lightVec,
                            light.getIntensity(),
                            isShadowed(p + norm*0.0001));
}

