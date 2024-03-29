#ifndef VOXELWORLD_H_
#define VOXELWORLD_H_

#include "math.h"
#include <iostream>
#include <stack>

#include "src/basicConstructs/Ray.h"
#include "src/utils/Utils.h"
#include "src/world/object/Intersection.h"
#include "src/world/lightSource/PointLight.h"

int getCubeIndex(int sideLength, int x, int y, int z);//get index of 3d coord in flattened cube

class VoxelWorld {
    private:
    int sideLengthPower;
    int* nPowers_int;
    float* nPowers_float;
    unsigned char* voxelTree;
    int* voxelTreeIndices;//indices of start of each boolean cube
    PointLight lightSource;
    public:
    VoxelWorld(unsigned char* voxels, int size, PointLight lightSource);
    ~VoxelWorld();
    int getSideLengthPower() const;
    unsigned char getVoxel(int index);
    bool intersectTopLevel(unsigned char* stack, float* stack2, const Ray& ray, float& v0x, float& v0y, float& v0z, bool& foundIntersection, bool& inside, Vec& norm, unsigned char& voxelType) const;
    bool getNextNeighbour(unsigned char* stack1, float* stack2, const Ray& ray, float& v0x, float& v0y, float& v0z, int& scale) const;
    void getChild(unsigned char* stack1, float* stack2, const Ray& ray, float& v0x, float& v0y, float& v0z, int& parentScale) const;
    bool intersect(const Ray& ray, unsigned char& voxelType, Point& point, Vec& norm) const;
    int getnPowersInt(int index) const;
    float getnPowersFloat(int index) const;
    int getVoxelTreeIndex(int index) const;//returns value of voxelTreeIndices at index
    IntersectionSpec getIntersection(const Ray& ray) const;
};

#endif