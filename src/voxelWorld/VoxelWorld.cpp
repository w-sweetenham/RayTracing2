#include "VoxelWorld.h"

int getCubeIndex(int sideLength, int x, int y, int z) {
    return x + sideLength*y + (sideLength*sideLength)*z;
}

VoxelWorld::VoxelWorld(unsigned char* voxels, int size) {
    float sizePower = std::log2(size);
    if(sizePower - (int)sizePower < 0.001 || sizePower - (int)sizePower > 0.999) {//check size is a power of 2
        int sideLength = std::cbrt(size);//N
        int sideLengthPower = round(std::log2(sideLength));//n
        this->sideLengthPower = sideLengthPower;
        int treeSize = size;
        for(int i=sideLengthPower-2; i>=0; i--) {
            treeSize += pow(2, 3*i);
        }
        voxelTree = new unsigned char[treeSize];
        for(int i=0; i<size; i++) {
            voxelTree[i] = voxels[i];
        }
        int startIndex = 0;
        int endIndex = size;//size points to start of current boolean cube
        for(int i=sideLengthPower-2; i>=0; i--) {
            if(i == sideLengthPower-2) {//first boolean cube
                int boolCubeSize = pow(2, i+1);//side length of boolean cube
                int boolCubeVol = pow(boolCubeSize,3);
                bool* booleanCube = new bool[boolCubeVol];
                for(int x=0; x<boolCubeSize; x++) {
                    for(int y=0; y<boolCubeSize; y++) {
                        for(int z=0; z<boolCubeSize; z++) {
                            int sum = 0;
                            sum += voxelTree[getCubeIndex(sideLength, 2*x, 2*y, 2*z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x + 1, 2*y, 2*z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x, 2*y + 1, 2*z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x + 1, 2*y + 1, 2*z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x, 2*y, 2*z + 1)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x + 1, 2*y, 2*z + 1)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x, 2*y + 1, 2*z + 1)];
                            sum += voxelTree[getCubeIndex(sideLength, 2*x + 1, 2*y + 1, 2*z + 1)];
                            booleanCube[getCubeIndex(boolCubeSize, x, y, z)] = sum > 0;
                        }
                    }
                }
                int byteCubeSize = pow(2, i);//side length of byte cube
                for(int x=0; x<byteCubeSize; x++) {
                    for(int y=0; y<byteCubeSize; y++) {
                        for(int z=0; z<byteCubeSize; z++) {
                            unsigned char byteRepresentation = 0;//byte representing its 8 corresponding boolean vals
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y, 2*z)];
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y, 2*z)] << 1;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y + 1, 2*z)] << 2;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y + 1, 2*z)] << 3;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y, 2*z + 1)] << 4;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y, 2*z + 1)] << 5;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y + 1, 2*z + 1)] << 6;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y + 1, 2*z + 1)] << 7;
                            voxelTree[endIndex + getCubeIndex(byteCubeSize, x, y, z)] = byteRepresentation;
                        }
                    }
                }
                delete [] booleanCube;
                startIndex = endIndex;
                endIndex += pow(byteCubeSize, 3);
            } else {
                int boolCubeSize = pow(2, i+1);//side length of boolean cube
                int boolCubeVol = pow(boolCubeSize, 3);
                bool* booleanCube = new bool[boolCubeVol];
                for(int x=0; x<boolCubeSize; x++) {
                    for(int y=0; y<boolCubeSize; y++) {
                        for(int z=0; z<boolCubeSize; z++) {
                            booleanCube[getCubeIndex(boolCubeSize, x, y, z)] = voxelTree[startIndex + getCubeIndex(boolCubeSize, x, y, z)] > 0;//boolean cube at this level is same size as byte cube at previous level
                        }
                    }
                }
                //boolean cube now created
                int byteCubeSize = pow(2, i);//side length of byte cube
                for(int x=0; x<byteCubeSize; x++) {
                    for(int y=0; y<byteCubeSize; y++) {
                        for(int z=0; z<byteCubeSize; z++) {
                            unsigned char byteRepresentation = 0;//byte representing its 8 corresponding boolean vals
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y, 2*z)];
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y, 2*z)] << 1;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y + 1, 2*z)] << 2;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y + 1, 2*z)] << 3;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y, 2*z + 1)] << 4;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y, 2*z + 1)] << 5;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x, 2*y + 1, 2*z + 1)] << 6;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2*x + 1, 2*y + 1, 2*z + 1)] << 7;
                            voxelTree[endIndex + getCubeIndex(byteCubeSize, x, y, z)] = byteRepresentation;
                        }
                    }
                }
                delete [] booleanCube;
                startIndex = endIndex;
                endIndex += pow(byteCubeSize, 3);
            }
        }
    }
}

VoxelWorld::~VoxelWorld() {
    delete [] voxelTree;
}

unsigned char VoxelWorld::getVoxel(int index) {
    return *(voxelTree + index);
}

int VoxelWorld::getSideLengthPower() const {
    return sideLengthPower;
}