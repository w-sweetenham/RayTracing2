#include "Shape.h"

Point2D Shape::getTexelPoint(const Point& globalPoint) const {
    return getTexelFromLocal(getLocalPoint(globalPoint));
}