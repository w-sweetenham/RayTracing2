#include "src/camera/Camera.h"
#include "src/world/World.h"
#include "src/world/lightSource/PointLight.h"
#include "src/world/object/shape/TSphere.h"
#include "src/world/object/material/Material.h"
#include "src/shader/Shader.h"
#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"

int main() {
    Camera cam(Point(0, 0, 0), Vec(0, 0, 1), Vec(0, 1, 0), 200, 400, 0.01, 0.0001);
    World world(PointLight(Point(0, 2, 0), Colour(1, 1, 1)));
    world.addMaterial(Material(0.1, 0.9, 0.9, 100, Colour(0, 0.5, 0.8)));
    world.addObject(TSphere(TranslationMat(0, 0, 2)), 0);
    PhongShader shader;
    std::cout << "Setup complete" << std::endl;
    cam.render(world, shader);
    std::cout << "Image created" << std::endl;
    cam.save("/home/william/CPP/Projects/RayTracer2/milestones/first3DImage/first3DImage.ppm");
}