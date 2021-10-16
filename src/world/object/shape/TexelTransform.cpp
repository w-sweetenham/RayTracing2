#include "TexelTransform.h"

Point2D TexelTransform::getTexel(const Point& point) const {
    return transform2DPoint(get2DPoint(point));
}

CubeTransform::CubeTransform(float scalingFactor): scalingFactor(scalingFactor) {}

Point2D CubeTransform::get2DPoint(const Point& localPoint) const {
    float x, y, z;
    x = localPoint.getElem(0);
    y = localPoint.getElem(1);
    z = localPoint.getElem(2);
    if(z < -0.999) {
        return Point2D((x+1.0)/2.0, (y+1.0)/2.0);
    }
    if(y > 0.999) {
        return Point2D((x+1.0)/2.0, (1.0-z)/2.0 + 1);
    }
    if(y < -0.999) {
        return Point2D((x+1.0)/2.0, (z+1.0)/2.0 - 1);
    }
    if(z > 0.999) {
        return Point2D((x+1.0)/2.0, (1.0-y)/2.0+2);
    }
    if(x > 0.999) {
        return Point2D((1.0-z)/2 + 1, (y+1)/2);
    }
    if(x < -0.999) {
        return Point2D((z-1.0)/2, (y+1)/2);
    }
}

Point2D CubeTransform::transform2DPoint(const Point2D& point) const {
    return Point2D(point.x*scalingFactor, point.y*scalingFactor);
}

SphereTransform::SphereTransform(float scalingFactor): scalingFactor(scalingFactor) {}
    
Point2D SphereTransform::get2DPoint(const Point& localPoint) const {
    float x2D, x3D, z3D;
    x3D = localPoint.getElem(0);
    z3D = localPoint.getElem(2);
    float ratio = (z3D/x3D);
    float theta;
    if(x3D >= 0) {
        theta = atan(ratio) + M_PI/2;
    } else {
        theta = atan(ratio) - M_PI/2;
    }
    return Point2D(theta, localPoint.getElem(1));
}
    
Point2D SphereTransform::transform2DPoint(const Point2D& point) const {
    return Point2D(scalingFactor*point.x, scalingFactor*point.y);
}