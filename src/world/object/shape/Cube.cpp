#include "Cube.h"

Cube::Cube(): MatTransformShape(), transform(1) {}

Cube::Cube(const Matrix& transformMat, float patternScaling): MatTransformShape(transformMat), transform(patternScaling) {}

Cube::Cube(const Cube& other): MatTransformShape(other.getMat()), transform(other.transform) {}

void checkAxis(float& tMin, float& tMax, float origin, float direction) {
    float tMinNumerator = (-1.0 - origin);
    float tmaxNumerator = (1.0 - origin);

    if(direction < 0.00001 && direction > -0.00001) {
        tMin = tMinNumerator * 100000000;
        tMax = tmaxNumerator * 100000000;
    } else {
        tMin = tMinNumerator/direction;
        tMax = tmaxNumerator/direction;
    }
    if(tMin > tMax) {
        float temp = tMin;
        tMin = tMax;
        tMax = temp;
    }
    return;
}

bool Cube::intersection(const Ray& ray, IntersectionSet& intSet, const Object* objPtr) const {
    Ray localRay = getLocalRay(ray);
    Point localOrigin = localRay.getOrigin();
    Vec localDirection = localRay.getDirection();
    float xTMin, xTMax;
    float yTMin, yTMax;
    float zTMin, zTMax;
    checkAxis(xTMin, xTMax, localOrigin.getElem(0), localDirection.getElem(0));
    checkAxis(yTMin, yTMax, localOrigin.getElem(1), localDirection.getElem(1));
    checkAxis(zTMin, zTMax, localOrigin.getElem(2), localDirection.getElem(2));

    float tMin = std::max(std::max(xTMin, yTMin), zTMin);
    float tMax = std::min(std::min(xTMax, yTMax), zTMax);

    if(tMin > tMax) {
        return false;
    } else {
        intSet.addIntersection(Intersection(tMin, objPtr));
        intSet.addIntersection(Intersection(tMax, objPtr));
        return true;
    }
}

Vec Cube::getNorm(const Point& point) const {
    Point objPoint = getLocalPoint(point);
    float xCompAbs, yCompAbs, zCompAbs;
    if(objPoint.getElem(0) >= 0) {
        xCompAbs = objPoint.getElem(0);
    } else {
        xCompAbs = objPoint.getElem(0) * -1.0;
    }
    if(objPoint.getElem(1) >= 0) {
        yCompAbs = objPoint.getElem(1);
    } else {
        yCompAbs = objPoint.getElem(1) * -1.0;
    }
    if(objPoint.getElem(2) >= 0) {
        zCompAbs = objPoint.getElem(2);
    } else {
        zCompAbs = objPoint.getElem(2) * -1.0;
    }

    float maxComp = std::max(std::max(xCompAbs, yCompAbs), zCompAbs);
    Vec localNorm;
    if(roughlyEqual(maxComp, xCompAbs)) {
        localNorm = Vec(objPoint.getElem(0), 0, 0);
    } else if(roughlyEqual(maxComp, yCompAbs)) {
        localNorm = Vec(0, objPoint.getElem(1), 0);
    } else {
        localNorm = Vec(0, 0, objPoint.getElem(2));
    }
    Vec worldNorm = getWorldVec(localNorm);
    worldNorm.normalize();
    return worldNorm;
}

Shape* Cube::clone() const {
    return new Cube(*this);
}

Point2D Cube::getTexelFromLocal(const Point& localPoint) const {
    return transform.getTexel(localPoint);
}