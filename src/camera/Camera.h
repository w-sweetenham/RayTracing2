#ifndef CAMERA_H_
#define CAMERA_H_

#include "src/basicConstructs/Tuple.h"
#include "src/camera/Canvas.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/World.h"

class Camera {
    private:
    Point origin;
    Vec xDirection;
    Vec yDirection;
    Vec zDirection;
    float focalLength;
    float pixSize;
    int numRows;
    int numCols;
    Canvas image;
    public:
    Camera(const Point& position, const Vec& zDir, const Vec& yDir, int numRows, int numCols, float focal, float pixSize);
    Ray getRay(int pixRow, int pixCol) const;
    Point getOrigin() const;
    Vec getX() const;
    Vec getY() const;
    Vec getZ() const;
    void render(World& world, int recursion);
    void save(std::string path) const;
};

#endif