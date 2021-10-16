#include "TSphere.h"

TSphere::TSphere(): MatTransformShape(), transform(1) {}

TSphere::TSphere(const Matrix& transformMat, float scalingFactor): MatTransformShape(transformMat), transform(scalingFactor) {}

TSphere::TSphere(const Matrix& transformMat): MatTransformShape(transformMat), transform(1) {}

TSphere::TSphere(const TSphere& other): MatTransformShape(other.getMat()), transform(other.transform) {}

bool TSphere::intersection(const Ray& ray, IntersectionSet& intSet, const Object* objPtr) const {
    Ray localRay = getLocalRay(ray);
    Point localOrigin = localRay.getOrigin();
    Vec localDirection = localRay.getDirection();
    Vec sphereToRay = localOrigin - Point(0.0, 0.0, 0.0);
    float a = localDirection.dot(localDirection);
    float b = 2.0 * localDirection.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1.0;
    float discriminant = (b*b) - (4*a*c);

    if(discriminant > 0.0) {
        float t1 = ((-1.0*b)+sqrt(discriminant))/(2*a);
        float t2 = ((-1.0*b)-sqrt(discriminant))/(2*a);
        Intersection i1(t1, objPtr);
        Intersection i2(t2, objPtr);
        intSet.addIntersection(i1);
        intSet.addIntersection(i2);
    }
}

Vec TSphere::getNorm(const Point& point) const {
    Point objPoint = getLocalPoint(point);
    Vec objNorm = objPoint - Point(0, 0, 0);
    Vec worldNorm = getWorldVec(objNorm);
    worldNorm.normalize();
    return worldNorm;
}

Shape* TSphere::clone() const {
    return new TSphere(*this);
}

Point2D TSphere::getTexelFromLocal(const Point& point) const {
   return transform.getTexel(point);
}