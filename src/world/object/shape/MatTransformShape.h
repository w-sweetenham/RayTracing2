#ifndef MATTRANSFORMSHAPE_H_
#define MATTRANSFORMSHAPE_H_

#include "src/basicConstructs/Matrix.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/object/shape/Shape.h"
#include "src/world/object/Intersection.h"

class MatTransformShape: public  Shape {
    private:
    Matrix mat;
    Matrix invMat;
    Matrix transInvMat;

    protected:
    Ray getLocalRay(const Ray& ray) const;
    Point getLocalPoint(const Point& point) const;
    Vec getWorldVec(const Vec& vec) const;

    public:
    MatTransformShape();
    MatTransformShape(const Matrix& transformMat);
    Matrix getMat() const;
    Matrix getInvMat() const;
    Matrix getTransInvMat() const;
    virtual bool intersection(const Ray& ray, IntersectionSet& intSet, const Object* objPtr) const = 0;
    virtual Vec getNorm(const Point& point) const = 0;
};

#endif