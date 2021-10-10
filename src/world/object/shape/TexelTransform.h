#include "src/basicConstructs/Tuple.h"

class TexelTransform {
    public:
    virtual Point2D get2DPoint(const Point& localPoint) const = 0;
    virtual Point2D transform2DPoint(const Point2D& point) const = 0;
    Point2D getTexel(const Point& point) const;
};

class CubeTransform : public TexelTransform {
    private:
    float scalingFactor;
    public:
    CubeTransform(float scalingFactor);
    Point2D get2DPoint(const Point& localPoint) const;
    Point2D transform2DPoint(const Point2D& point) const;
};