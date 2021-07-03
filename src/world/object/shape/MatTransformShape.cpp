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