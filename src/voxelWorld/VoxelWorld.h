#ifndef VOXELWORLD_H_
#define VOXELWORLD_H_

#include "math.h"
#include <iostream>
#include <stack>

#include "src/basicConstructs/Ray.h"

int getCubeIndex(int sideLength, int x, int y, int z);//get index of 3d coord in flattened cube

class VoxelWorld {
    private:
    int sideLengthPower;
    int* nPowers;
    unsigned char* voxelTree;
    public:
    VoxelWorld(unsigned char* voxels, int size);
    ~VoxelWorld();
    int getSideLengthPower() const;
    unsigned char getVoxel(int index);
    bool intersectTopLevel(unsigned char* stack, const Ray& ray) const;
    int getnPowers(int index) const;
};

#endif