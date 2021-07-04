#include "src/world/object/shape/Shape.h"
#include "src/world/object/material/Material.h"

class Object {
    private:
    Shape* shape;
    std::string materialName;
};