#include "TestVoxelWorld.h"

void TestVoxelWorld::setUp() {
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
                } else {
                    voxelVals[getCubeIndex(8, x, y, z)] = 7;
                }
            }
        }
    }
    vWorld = new VoxelWorld(voxelVals, 512, PointLight(Point(6, 9, 7.5), Colour(0.9, 0.9, 0.9)));
}

void TestVoxelWorld::tearDown() {}

void TestVoxelWorld::testVoxelWorldInitialization() {
    /*
    * This test builds a voxel tree structure from an input array representing a cube of voxels each with their value stored as an unsigned char.
    * It goes through each scale of voxel cube and checks a set of indexes to make sure the correct values are set
    */

    CPPUNIT_ASSERT(vWorld->getSideLengthPower() == 3);

    CPPUNIT_ASSERT(vWorld->getVoxelTreeIndex(0) == 512);
    CPPUNIT_ASSERT(vWorld->getVoxelTreeIndex(1) == 520);

    CPPUNIT_ASSERT(vWorld->getnPowersInt(0) == 1);
    CPPUNIT_ASSERT(vWorld->getnPowersInt(1) == 2);
    CPPUNIT_ASSERT(vWorld->getnPowersInt(2) == 4);
    CPPUNIT_ASSERT(vWorld->getnPowersInt(3) == 8);

    CPPUNIT_ASSERT(roughlyEqual(vWorld->getnPowersFloat(0), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(vWorld->getnPowersFloat(1), 2.0));
    CPPUNIT_ASSERT(roughlyEqual(vWorld->getnPowersFloat(2), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(vWorld->getnPowersFloat(3), 8.0));

    /*
     * scale 1 checks
     */

    CPPUNIT_ASSERT(vWorld->getVoxel(0) == 0);
    CPPUNIT_ASSERT(vWorld->getVoxel(8) == 0);
    CPPUNIT_ASSERT(vWorld->getVoxel(10) == 7);
    CPPUNIT_ASSERT(vWorld->getVoxel(457) == 0);
    CPPUNIT_ASSERT(vWorld->getVoxel(465) == 7);
    CPPUNIT_ASSERT(vWorld->getVoxel(458) == 7);

    /*
     * scale 2 checks
     */

    CPPUNIT_ASSERT(vWorld->getVoxel(512) == 14);
    CPPUNIT_ASSERT(vWorld->getVoxel(513) == 15);
    CPPUNIT_ASSERT(vWorld->getVoxel(514) == 15);
    CPPUNIT_ASSERT(vWorld->getVoxel(515) == 15);
    CPPUNIT_ASSERT(vWorld->getVoxel(516) == 238);
    CPPUNIT_ASSERT(vWorld->getVoxel(517) == 0);
    CPPUNIT_ASSERT(vWorld->getVoxel(518) == 255);
    CPPUNIT_ASSERT(vWorld->getVoxel(519) == 0);

    /*
     * scale 3 checks
     */
    CPPUNIT_ASSERT(vWorld->getVoxel(520) == 95);
}

void TestVoxelWorld::testTopLevelIntersection() {
    unsigned char stack1[9];
    float stack2[9];
    Ray rayMiss1(Point(-4, 4, 4), Vec(1, -2, 0));
    Ray rayMiss2(Point(4, 4, -4), Vec(0, -2, 1));
    Ray rayMiss3(Point(12, 4, 4), Vec(-1, 2, 0));

    float v0x, v0y, v0z;

    bool foundValidCube;
    unsigned char voxelType;
    Vec norm;
    bool isInside;

    CPPUNIT_ASSERT(vWorld->intersectTopLevel(stack1, stack2, rayMiss1, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType) == false);
    CPPUNIT_ASSERT(vWorld->intersectTopLevel(stack1, stack2, rayMiss2, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType) == false);
    CPPUNIT_ASSERT(vWorld->intersectTopLevel(stack1, stack2, rayMiss2, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType) == false);

    bool hit;

    Ray rayIndex0(Point(-1, 3.1, 1.1), Vec(1.0, 0.1, 0.1));
    hit = vWorld->intersectTopLevel(stack1, stack2, rayIndex0, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    CPPUNIT_ASSERT(stack1[2] == 1);
    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 3.2));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 1.2));
    CPPUNIT_ASSERT(isInside == false);

    Ray rayIndex5(Point(6, -1, 7), Vec(0, 1, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, rayIndex5, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 5);
    CPPUNIT_ASSERT(stack1[2] == 2);
    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 4));
    CPPUNIT_ASSERT(roughlyEqual(v0x, 6));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 7));
    CPPUNIT_ASSERT(isInside == false);

    Ray rayIndex6(Point(-1, 6, 7), Vec(1, 0, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, rayIndex6, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 6);
    CPPUNIT_ASSERT(stack1[2] == 1);
    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 4));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 6));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 7));
    CPPUNIT_ASSERT(isInside == false);

    Ray rayIndex7(Point(6, 9, 7), Vec(-1, -1, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, rayIndex7, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 7);
    CPPUNIT_ASSERT(stack1[2] == 10);
    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 4));
    CPPUNIT_ASSERT(roughlyEqual(v0x, 5));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 7));
    CPPUNIT_ASSERT(isInside == false);

    Ray r8(Point(0.5, 0.5, 3.1), Vec(0, 0, -1));
    hit = vWorld->intersectTopLevel(stack1, stack2, r8, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 4);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 4);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 2));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 3));
    
    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == false);
    

    Ray r9(Point(1.5, 1.5, 0.9), Vec(-1, 0, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, r9, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);

    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 0);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 3);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 1));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 1));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 0));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == false);

    Ray r10(Point(1.5, 3.1, 3.1), Vec(1, 0, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, r10, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 6);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 7);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 2));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 1));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 3));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 3));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == false);

    Ray r11(Point(3.5, 3.2, 3.5), Vec(0, 0, 1));
    hit = vWorld->intersectTopLevel(stack1, stack2, r11, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);
    
    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 7);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 7);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 2));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 3));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 3));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 3));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == false);


    Ray r12(Point(7.5, 7.5, 7.5), Vec(-1, 0, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, r12, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);

    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 7);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 7);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 7);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 4));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 6));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 6));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 6));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 7));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 7));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 7));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == false);

    Ray r13(Point(2.2, 0.5, 0.5), Vec(-1, 0, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, r13, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);

    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 1);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 0);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 0));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == true);

    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(1, 0, 0)));

    Ray r14(Point(0.5, 2.9, 0.5), Vec(0, -1, 0));
    hit = vWorld->intersectTopLevel(stack1, stack2, r14, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);

    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 0);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 2);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 0);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 0));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 2));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 0));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == true);

    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 1, 0)));

    Ray r15(Point(6.3, 7.2, 1.8), Vec(0.1, 0, 1));
    hit = vWorld->intersectTopLevel(stack1, stack2, r15, v0x, v0y, v0z, foundValidCube, isInside, norm, voxelType);
    CPPUNIT_ASSERT(hit == true);

    CPPUNIT_ASSERT(stack1[0] == 3);
    CPPUNIT_ASSERT(stack1[1] == 3);
    //don't care about entry plane at each scale here
    CPPUNIT_ASSERT(stack1[3] == 2);
    CPPUNIT_ASSERT(stack1[4] == 3);
    
    CPPUNIT_ASSERT(stack1[6] == 1);
    CPPUNIT_ASSERT(stack1[7] == 6);

    CPPUNIT_ASSERT(roughlyEqual(stack2[0], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[1], 4));
    CPPUNIT_ASSERT(roughlyEqual(stack2[2], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[3], 6));
    CPPUNIT_ASSERT(roughlyEqual(stack2[4], 6));
    CPPUNIT_ASSERT(roughlyEqual(stack2[5], 0));

    CPPUNIT_ASSERT(roughlyEqual(stack2[6], 6));
    CPPUNIT_ASSERT(roughlyEqual(stack2[7], 7));
    CPPUNIT_ASSERT(roughlyEqual(stack2[8], 1));

    CPPUNIT_ASSERT(isInside == true);
    CPPUNIT_ASSERT(foundValidCube == true);

    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 0, -1)));
}

void TestVoxelWorld::testGetNextCube() {
    unsigned char stack1_1[6] = {3, 0, 2, 2, 3, 2};
    float stack2_1[6] = {0, 0, 0, 2, 2, 0};
    float v0x, v0y, v0z;
    v0x = 3;
    v0y = 2;
    v0z = 0.5;
    int scale = 2;
    bool isNeighbour = vWorld->getNextNeighbour(stack1_1, stack2_1, Ray(Point(3, -1, 0.5), Vec(0, 1, 0)), v0x, v0y, v0z, scale);
    CPPUNIT_ASSERT(isNeighbour);
    unsigned char stack1Correct_1[6] = {3, 2, 2, 2, 3, 2};
    for(int i=0; i<6; i++) {
        CPPUNIT_ASSERT(stack1Correct_1[i] == stack1_1[i]);
    }
    float stack2Correct_1[6] = {0, 4, 0, 2, 2, 0};
    for(int i=0; i<6; i++) {
        CPPUNIT_ASSERT(roughlyEqual(stack2Correct_1[i], stack2_1[i]));
    }
    CPPUNIT_ASSERT(roughlyEqual(v0x, 3));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 4));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 0.5));
    CPPUNIT_ASSERT(scale == 3);


    unsigned char stack1_2[9] = {3, 3, 9, 2, 0, 9, 1, 2, 9};
    float stack2_2[9] = {4, 4, 0, 4, 4, 0, 4, 5, 0};
    v0x = 5;
    v0y = 5.5;
    v0z = 0.5;
    scale = 1;
    isNeighbour = vWorld->getNextNeighbour(stack1_2, stack2_2, Ray(Point(9, 5.5, 0.5), Vec(-1, 0, 0)), v0x, v0y, v0z, scale);
    CPPUNIT_ASSERT(isNeighbour);
    unsigned char stack1Correct_2[3] = {3, 2, 9};
    for(int i=0; i<3; i++) {
        CPPUNIT_ASSERT(stack1Correct_2[i] == stack1_2[i]);
    }
    float stack2Correct_2[3] = {0, 4, 0};
    for(int i=0; i<3; i++) {
        CPPUNIT_ASSERT(roughlyEqual(stack2Correct_2[i], stack2_2[i]));
    }
    CPPUNIT_ASSERT(roughlyEqual(v0x, 4));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 5.5));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 0.5));
    CPPUNIT_ASSERT(scale == 3);


    unsigned char stack1_3[3] = {3, 6, 1};
    float stack2_3[3] = {0, 4, 4};
    v0x = 0;
    v0y = 7;
    v0z = 6;
    scale = 3;
    isNeighbour = vWorld->getNextNeighbour(stack1_3, stack2_3, Ray(Point(-1, 7, 6), Vec(1, 0, 0)), v0x, v0y, v0z, scale);
    CPPUNIT_ASSERT(isNeighbour);
    unsigned char stack1Correct_3[3] = {3, 7, 1};
    for(int i=0; i<3; i++) {
        CPPUNIT_ASSERT(stack1Correct_3[i] == stack1_3[i]);
    }
    float stack2Correct_3[3] = {4, 4, 4};
    for(int i=0; i<3; i++) {
        CPPUNIT_ASSERT(roughlyEqual(stack2Correct_3[i], stack2_3[i]));
    }
    CPPUNIT_ASSERT(roughlyEqual(v0x, 4));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 7));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 6));
    CPPUNIT_ASSERT(scale == 3);


    unsigned char stack1_4[6] = {3, 0, 12, 2, 2, 12};
    float stack2_4[6] = {0, 0, 0, 0, 2, 0};
    v0x = 0.5;
    v0y = 3;
    v0z = 2;
    scale = 2;
    isNeighbour = vWorld->getNextNeighbour(stack1_4, stack2_4, Ray(Point(1, 3, 9), Vec(0, 0, -1)), v0x, v0y, v0z, scale);
    CPPUNIT_ASSERT(!isNeighbour);
}

void TestVoxelWorld::testGetChildCube() {
    unsigned char stack1_1[6] = {3, 3, 9, 2, 3, 2};
    float stack2_1[6] = {4, 4, 0, 1, 1, 3};//initializing second parts of stacks randomly as can't guarantee it will be 0
    float v0x, v0y, v0z;
    v0x = 8;
    v0y = 5;
    v0z = 1;
    int scale = 3;
    vWorld->getChild(stack1_1, stack2_1, Ray(Point(9, 5, 1), Vec(-1, 0, 0)), v0x, v0y, v0z, scale);
    unsigned char stack1Correct_1[6] = {3, 3, 9, 2, 1, 9};
    for(int i=0; i<6; i++) {
        CPPUNIT_ASSERT(stack1Correct_1[i] == stack1_1[i]);
    }
    float stack2Correct_1[6] = {4, 4, 0, 6, 4, 0};
    for(int i=0; i<6; i++) {
        CPPUNIT_ASSERT(roughlyEqual(stack2Correct_1[i], stack2_1[i]));
    }
    CPPUNIT_ASSERT(roughlyEqual(v0x, 8));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 5));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 1));
    CPPUNIT_ASSERT(scale == 2);

    unsigned char stack1_2[9] = {3, 0, 2, 1, 7, 1, 4, 2, 2};
    float stack2_2[9] = {0, 0, 0, 1, 1, 3, 1, 1, 3};//initializing second parts of stacks randomly as can't guarantee it will be 0
    v0x = 3.5;
    v0y = 0;
    v0z = 0.5;
    scale = 3;
    vWorld->getChild(stack1_2, stack2_2, Ray(Point(3.5, -1, 0.5), Vec(0, 1, 0)), v0x, v0y, v0z, scale);
    vWorld->getChild(stack1_2, stack2_2, Ray(Point(3.5, -1, 0.5), Vec(0, 1, 0)), v0x, v0y, v0z, scale);
    unsigned char stack1Correct_2[9] = {3, 0, 2, 2, 1, 2, 1, 1, 2};
    for(int i=0; i<9; i++) {
        CPPUNIT_ASSERT(stack1Correct_2[i] == stack1_2[i]);
    }
    float stack2Correct_2[9] = {0, 0, 0, 2, 0, 0, 3, 0, 0};
    for(int i=0; i<9; i++) {
        CPPUNIT_ASSERT(roughlyEqual(stack2Correct_2[i], stack2_2[i]));
    }
    CPPUNIT_ASSERT(roughlyEqual(v0x, 3.5));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 0));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 0.5));
    CPPUNIT_ASSERT(scale == 1);

    unsigned char stack1_3[9] = {3, 3, 4, 1, 7, 1, 4, 2, 2};
    float stack2_3[9] = {4, 4, 0, 1, 1, 3, 1, 1, 3};//initializing second parts of stacks randomly as can't guarantee it will be 0
    v0x = 5.5;
    v0y = 5.5;
    v0z = 0;
    scale = 3;
    vWorld->getChild(stack1_3, stack2_3, Ray(Point(5.5, 5.5, -1), Vec(0, 0, 1)), v0x, v0y, v0z, scale);
    vWorld->getChild(stack1_3, stack2_3, Ray(Point(5.5, 5.5, -1), Vec(0, 0, 1)), v0x, v0y, v0z, scale);
    unsigned char stack1Correct_3[9] = {3, 3, 4, 2, 0, 4, 1, 3, 4};
    for(int i=0; i<9; i++) {
        CPPUNIT_ASSERT(stack1Correct_3[i] == stack1_3[i]);
    }
    float stack2Correct_3[9] = {4, 4, 0, 4, 4, 0, 5, 5, 0};
    for(int i=0; i<9; i++) {
        CPPUNIT_ASSERT(roughlyEqual(stack2Correct_3[i], stack2_3[i]));
    }
    CPPUNIT_ASSERT(roughlyEqual(v0x, 5.5));
    CPPUNIT_ASSERT(roughlyEqual(v0y, 5.5));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 0));
    CPPUNIT_ASSERT(scale == 1);
}

void TestVoxelWorld::testIntersect() {
    Point p;
    Vec norm;
    bool hit;
    unsigned char voxelType;

    /*
     * Tests for intersecting from outside of voxel world
     */


    Ray r1(Point(1, 1, -1), Vec(0, 0, 1));
    hit = vWorld->intersect(r1, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);
    std::cout << std::endl;

    Ray r2(Point(1, -1, 0.5), Vec(1, 1.5, 0));
    hit = vWorld->intersect(r2, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(2, 0.5, 0.5)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(-1, 0, 0)));
    std::cout << std::endl;

    Ray r3(Point(6, 5, 9), Vec(0, 0, -1));
    hit = vWorld->intersect(r3, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(6, 5, 2)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 0, 1)));
    std::cout << std::endl;

    Ray r4(Point(10, 6, 6), Vec(-2, 0, -1));
    hit = vWorld->intersect(r4, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(2, 6, 2)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 0, 1)));
    std::cout << std::endl;

    Ray r5(Point(9, 2, 3), Vec(-1, 0, 0));
    hit = vWorld->intersect(r5, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);
    std::cout << std::endl;

    Ray r6(Point(9, 2, 3), Vec(0, 1, 2));
    hit = vWorld->intersect(r6, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);
    std::cout << std::endl;

    Ray r7(Point(6, 5, 9), Vec(0, 0, 11));
    hit = vWorld->intersect(r7, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);
    std::cout << std::endl;

    /*
     * Tests for intersecting from inside of voxel world
     */


    Ray r8(Point(0.5, 0.5, 3), Vec(0, 0, -1));
    hit = vWorld->intersect(r8, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);

    Ray r9(Point(1.5, 1.5, 1), Vec(-1, 0, 0));
    hit = vWorld->intersect(r9, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);

    Ray r10(Point(1.5, 3, 3), Vec(1, 0, 0));
    hit = vWorld->intersect(r10, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == false);

    Ray r11(Point(3.5, 3, 3.5), Vec(0, 0, 1));
    hit = vWorld->intersect(r11, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(3.5, 3, 4)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 0, -1)));

    Ray r12(Point(7.5, 7.5, 7.5), Vec(-1, 0, 0));
    hit = vWorld->intersect(r12, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(4, 7.5, 7.5)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(1, 0, 0)));


    Ray r13(Point(2.2, 0.5, 0.5), Vec(-1, 0, 0));
    hit = vWorld->intersect(r13, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(2, 0.5, 0.5)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(1, 0, 0)));

    Ray r14(Point(0.5, 2.9, 0.5), Vec(0, -1, 0));
    hit = vWorld->intersect(r14, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(0.5, 2, 0.5)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 1, 0)));

    Ray r15(Point(6, 7, 1.1), Vec(0, 0, 1));
    hit = vWorld->intersect(r15, voxelType, p, norm);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(voxelType == 7);
    CPPUNIT_ASSERT(p.roughlyEqual(Point(6, 7, 2)));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0, 0, -1)));

}

void TestVoxelWorld::testGetIntersection() {
    Ray r1(Point(0.5, 0.5, 3), Vec(0, 0, -1));
    IntersectionSpec intSpec1 = vWorld->getIntersection(r1);
    CPPUNIT_ASSERT(intSpec1.hit == false);

    Ray r2(Point(7.5, 7.5, 7.5), Vec(-1, 0, 0));
    IntersectionSpec intSpec2 = vWorld->getIntersection(r2);
    CPPUNIT_ASSERT(intSpec2.hit == true);
    CPPUNIT_ASSERT(intSpec2.norm.roughlyEqual(Vec(1, 0, 0)));
    CPPUNIT_ASSERT(intSpec2.point.roughlyEqual(Point(4, 7.5, 7.5)));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.ambient, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.diffuse, 0.8));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.specular, 0.7));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.shininess, 100));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.n1, 1));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.n2, 1.3));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.reflectivity, 0));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.transparency, 0));
    CPPUNIT_ASSERT(intSpec2.colour.roughlyEqual(Colour(0.1, 0.8, 0.3)));
    CPPUNIT_ASSERT(intSpec2.lightVec.roughlyEqual(Vec(0.8, 0.6, 0)));
    CPPUNIT_ASSERT(intSpec2.lightIntensity.roughlyEqual(Colour(0.9, 0.9, 0.9)));
    CPPUNIT_ASSERT(intSpec2.isShadowed == false);
}

CppUnit::Test* TestVoxelWorld::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Voxel World Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test voxel world", &TestVoxelWorld::testVoxelWorldInitialization));

    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test top-level intersection", &TestVoxelWorld::testTopLevelIntersection));
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test get next cube", &TestVoxelWorld::testGetNextCube));
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test get child cube", &TestVoxelWorld::testGetChildCube));
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test intersection", &TestVoxelWorld::testIntersect));
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test intersection", &TestVoxelWorld::testGetIntersection));

    return testSuite;
}