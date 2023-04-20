#include <filesystem>
#include <iostream>

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
    Camera cam(Point(0, 3.0, -6), Vec(0, -1.0, 5), Vec(0, 1, 0), 800, 1600, 0.02, 0.000025);
    World world(PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));
    world.addObject(TSphere(TranslationMat(1.5, 1, -1.0), 4), PatternMaterial(0.2, 0.6, 0.8, 100, CheckerPattern(Colour(0, 0.2, 0.9), Colour(0.83, 0.69, 0.22)), 1.33, 0.1, 0));
    world.addObject(Cube(TranslationMat(0, -0.1, 2)*ScalingMat(1000, 0.2, 1000), 1000), PatternMaterial(0.2, 0.8, 0.6, 100, CheckerPattern(Colour(0, 0, 0), Colour(1, 1, 1)), 1.5, 0.1, 0));
    world.addObject(Cube(TranslationMat(0, 0, 8)*ScalingMat(1000, 1000, 0.1), 3000), PatternMaterial(0.2, 0.8, 0.6, 100, CheckerPattern(Colour(0, 0, 0), Colour(1, 1, 1)), 1.5, 0.1, 0));
    world.addObject(TSphere(TranslationMat(-4.0, 1.5, 1.3)*ScalingMat(1.5, 1.5, 1.5)), basicMaterial(0.2, 0.2, 0.8, 100, Colour(0.5, 0.5, 0.8), 1.33, 0, 0));
    world.addObject(Cube(TranslationMat(0, 2, 2)*ScalingMat(2, 2, 2)*YRotation(20), 10), basicMaterial(0.2, 0.8, 0.6, 100, Colour(0.1, 0.1, 0.5), 1.5, 0.1, 0));
    PhongShader shader;
    std::cout << "Setup complete" << std::endl;
    cam.render(world, shader, 50);
    std::cout << "Image created" << std::endl;
    std::filesystem::path save_path = std::filesystem::current_path() / "example1.ppm";
    cam.save(save_path);
}