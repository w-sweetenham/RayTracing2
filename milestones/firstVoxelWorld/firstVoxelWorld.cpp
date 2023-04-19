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
#include "src/voxelWorld/VoxelWorld.h"

int main() {
    unsigned char voxelVals[512];
    int count = 0;
    for(int z=0; z<8; z++) {
        for(int y=0; y<8; y++) {
            for(int x=0; x<8; x++) {
                if(x <= 1 && y <= 1) {
                    voxelVals[getCubeIndex(8, x, y, z)] = 0;
                } else if(z == 3 || z == 2) {
                    voxelVals[getCubeIndex(8, x, y, z)] = 0;
                } else if(z >= 4 && x >=4) {
                    voxelVals[getCubeIndex(8, x, y, z)] = 0;
                } else if(y == 5 && z == 5) {
                    voxelVals[getCubeIndex(8, x, y, z)] = 0;
                } else {
                    voxelVals[getCubeIndex(8, x, y, z)] = 7;
                }
            }
        }
    }
    VoxelWorld vWorld(voxelVals, 512, PointLight(Point(6, 9, 7.5), Colour(0.9, 0.9, 0.9)));
    Camera cam(Point(30, 4, 4.5), Vec(-1, 0, 0), Vec(0, 1, 0), 200, 400, 0.05, 0.0001);
    PhongShader shader;
    std::cout << "Setup complete" << std::endl;
    cam.render(vWorld, shader, 10);
    std::cout << "Image created" << std::endl;
    std::filesystem::path cwd = std::filesystem::current_path() / "firstVoxelWorld.ppm";
    cam.save(cwd.string());
}