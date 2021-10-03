#include "src/camera/Camera.h"
#include "src/world/World.h"
#include "src/world/lightSource/PointLight.h"
#include "src/world/object/shape/TSphere.h"
#include "src/world/object/shape/Cube.h"
#include "src/world/object/material/Material.h"
#include "src/shader/Shader.h"
#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"

int main() {
    Camera cam(Point(0, 1.5, -5), Vec(0, -0.5, 5), Vec(0, 1, 0), 200, 400, 0.02, 0.0001);
    World world(PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));
    world.addMaterial(Material(0.0, 0.0, 0.8, 100, Colour(0, 0.5, 0.8), 1.33, 0, 0.95));
    world.addMaterial(Material(0.2, 0.8, 0.6, 100, Colour(0, 0.5, 0.4), 1.5, 0.1, 0));
    world.addMaterial(Material(0.1, 0.9, 0.9, 100, Colour(0, 0.4, 0.5), 1.5, 0.05, 0));
    world.addObject(TSphere(TranslationMat(-0.5, 1, 5.5)), 2);
    world.addObject(Cube(TranslationMat(0, -0.1, 2)*ScalingMat(1000, 0.2, 1000)), 1);
    world.addObject(Cube(TranslationMat(0, 0, 8)*ScalingMat(1000, 1000, 0.1)), 2);
    world.addObject(TSphere(TranslationMat(0.0, 1, -1.5)*ScalingMat(1, 1, 1)), 0);
    PhongShader shader;
    std::cout << "Setup complete" << std::endl;
    cam.render(world, shader, 50);
    std::cout << "Image created" << std::endl;
    cam.save("/home/william/CPP/Projects/RayTracer2/milestones/firstRefractionReflection/firstRefracionReflection.ppm");
}