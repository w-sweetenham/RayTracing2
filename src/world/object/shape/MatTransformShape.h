#ifndef MATTRANSFORMSHAPE_H_
#define MATTRANSFORMSHAPE_H_

#include "src/basicConstructs/Matrix.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/object/shape/Shape.h"

class MatTransformShape: public  Shape {
    private:
    Matrix mat;
    Matrix invMat;
    Matrix transInvMat;

    protected:
    Ray getLocalRay(const Ray& ray);

    public:
    MatTransformShape();
    MatTransformShape(const Matrix& transformMat);
    Matrix getMat() const;
    Matrix getInvMat() const;
    Matrix getTransInvMat() const;
    virtual bool intersection(const Ray& ray, float& t) const = 0;
    virtual Vec getNorm(const Point& point) const = 0;
};

#endif