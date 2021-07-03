#include "TSphere.h"

TSphere::TSphere(): MatTransformShape() {}

TSphere::TSphere(const Matrix& transformMat): MatTransformShape(transformMat) {}

TSphere::TSphere(const TSphere& other): MatTransformShape(other.getMat()) {}

bool TSphere::intersection(const Ray& ray, float& t) const {
    return true;
}

Vec TSphere::getNorm(const Point& point) const {
    return Vec(1, 1 ,1);
}