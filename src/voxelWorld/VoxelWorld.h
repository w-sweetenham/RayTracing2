#ifndef VOXELWORLD_H_
#define VOXELWORLD_H_

#include "math.h"
#include <iostream>

int getCubeIndex(int sideLength, int x, int y, int z);//get index of 3d coord in flattened cube

class VoxelWorld {
    private:
    unsigned char* voxelTree;
    public:
    VoxelWorld(unsigned char* voxels, int size);
    ~VoxelWorld();
    unsigned char getVoxel(int index);
};

#endif