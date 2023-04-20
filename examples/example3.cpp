#include <filesystem>
#include <iostream>
#include <time.h>

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
    Camera cam(Point(0.4, 8.0, -20), Vec(-0.1, -1.2, 5), Vec(0, 1, 0), 800, 1600, 0.02, 0.000006125);
    World world(PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));
    world.addObject(Cube(TranslationMat(0, -0.1, 2)*ScalingMat(1000, 0.2, 1000), 4000), PatternMaterial(0.2, 0.8, 0.6, 100, CheckerPattern(Colour(0, 0, 0), Colour(1, 1, 1)), 1.5, 0.1, 0));
    world.addObject(Cube(TranslationMat(0, 0, 30)*ScalingMat(1000, 1000, 0.1), 1000), PatternMaterial(0.2, 0.8, 0.6, 100, CheckerPattern(Colour(0, 0, 0), Colour(1, 1, 1)), 1.5, 0.25, 0));
    
    std::srand((unsigned) time(NULL));
    for (int row=1; row <= 6; row++) {
        if (row % 2 == 0) {
            for (int x_index=0; x_index < row/2; x_index++) {
                float red_l = ((float) rand())/RAND_MAX;
                float green_l = ((float) rand())/RAND_MAX;
                float blue_l = ((float) rand())/RAND_MAX;
                world.addObject(TSphere(TranslationMat(-1 - 2*x_index, 1, row*2), 4), basicMaterial(0.4, 0.6, 0.8, 100, Colour(red_l, green_l, blue_l), 1, 0, 0));

                float red_r = ((float) rand())/RAND_MAX;
                float green_r = ((float) rand())/RAND_MAX;
                float blue_r = ((float) rand())/RAND_MAX;
                world.addObject(TSphere(TranslationMat(1 + 2*x_index, 1, row*2), 4), basicMaterial(0.4, 0.6, 0.8, 100, Colour(red_r, green_r, blue_r), 1, 0, 0));
            }
        } else {
            for (int x_index=1; x_index <= (int)(row/2); x_index++) {
                float red_l = ((float) rand())/RAND_MAX;
                float green_l = ((float) rand())/RAND_MAX;
                float blue_l = ((float) rand())/RAND_MAX;
                world.addObject(TSphere(TranslationMat(-2*(x_index), 1, row*2), 4), basicMaterial(0.4, 0.6, 0.8, 100, Colour(red_l, green_l, blue_l), 1, 0, 0));

                float red_r = ((float) rand())/RAND_MAX;
                float green_r = ((float) rand())/RAND_MAX;
                float blue_r = ((float) rand())/RAND_MAX;
                world.addObject(TSphere(TranslationMat(2*x_index, 1, row*2), 4), basicMaterial(0.4, 0.6, 0.8, 100, Colour(red_r, green_r, blue_r), 1, 0, 0));
            }
                float red_c = ((float) rand())/RAND_MAX;
                float green_c = ((float) rand())/RAND_MAX;
                float blue_c = ((float) rand())/RAND_MAX;
                world.addObject(TSphere(TranslationMat(0, 1, row*2), 4), basicMaterial(0.4, 0.6, 0.8, 100, Colour(red_c, green_c, blue_c), 1, 0, 0));
        }
    }

    PhongShader shader;
    std::cout << "Setup complete" << std::endl;
    cam.render(world, shader, 30);
    std::cout << "Image created" << std::endl;
    std::filesystem::path save_path = std::filesystem::current_path() / "example3.ppm";
    cam.save(save_path);
}