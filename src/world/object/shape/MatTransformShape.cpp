#include "MatTransformShape.h"

MatTransformShape::MatTransformShape() : mat(IdentityMat()), invMat(IdentityMat()), transInvMat(IdentityMat()) {}

MatTransformShape::MatTransformShape(const Matrix &transformMat): mat(transformMat), invMat(transformMat.getInverse()), transInvMat(transformMat.getInverse().transpose()) {}

Matrix MatTransformShape::getMat() const {
    return mat;
}

Matrix MatTransformShape::getInvMat() const {
    return invMat;
}

Matrix MatTransformShape::getTransInvMat() const {
    return transInvMat;
}

Ray MatTransformShape::getLocalRay(const Ray& ray) const {
    return ray.transform(invMat);
}

Point MatTransformShape::getLocalPoint(const Point& point) const {
    return invMat * point;
}

Vec MatTransformShape::getWorldVec(const Vec& vec) const {
    return transInvMat * vec;
}