#include "Camera.h"

Camera::Camera(const Point& position, const Vec& zDir, const Vec& yDir, int numRows, int numCols, float focal, float pixSize): origin(position), image(numRows, numCols),  focalLength(focal), pixSize(pixSize), numRows(numRows), numCols(numCols) {
    zDirection = zDir;
    zDirection.normalize();
    xDirection = yDir * zDir;
    xDirection.normalize();
    yDirection = zDirection * xDirection;
    yDirection.normalize();
}

Ray Camera::getRay(int pixRow, int pixCol) const {
    float xFactor;
    float yFactor;

    if(numCols % 2 == 0) {
        xFactor = pixSize * (0.5 - numCols/2 + pixCol);
    } else {
        xFactor = pixSize * (pixCol - numCols/2);
    }

    if(numRows % 2 == 0) {
        yFactor = pixSize * (numRows/2 - 0.5 - pixRow);
    } else {
        yFactor = pixSize * (numRows/2 - pixRow);
    }

    Vec direction = zDirection*focalLength + xDirection*xFactor + yDirection*yFactor;
    return Ray(origin, direction);
}

Point Camera::getOrigin() const {
    return origin;
}
    
Vec Camera::getX() const {
    return xDirection;
}
    
Vec Camera::getY() const {
    return yDirection;
}

Vec Camera::getZ() const {
    return zDirection;
}

void Camera::render(const World& world, const Shader& shader, int recursion) {
    for(int row=0; row<numRows; row++) {
        for(int col=0; col<numCols; col++) {
            Colour c = shader.getColour(getRay(row, col), world, recursion);
            image.setPixel(row, col, c);
        }
    }
}
    
void Camera::save(std::string path) const {
    image.saveImage(path);
}

