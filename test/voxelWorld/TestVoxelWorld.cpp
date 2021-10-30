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
    vWorld = new VoxelWorld(voxelVals, 512);
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
    unsigned char stack[6];
    Ray rayMiss1(Point(-4, 4, 4), Vec(1, -2, 0));
    Ray rayMiss2(Point(4, 4, -4), Vec(0, -2, 1));
    Ray rayMiss3(Point(12, 4, 4), Vec(-1, 2, 0));

    float v0x, v0y, v0z;

    CPPUNIT_ASSERT(vWorld->intersectTopLevel(stack, rayMiss1, v0x, v0y, v0z) == false);
    CPPUNIT_ASSERT(vWorld->intersectTopLevel(stack, rayMiss2, v0x, v0y, v0z) == false);
    CPPUNIT_ASSERT(vWorld->intersectTopLevel(stack, rayMiss2, v0x, v0y, v0z) == false);

    bool hit;

    Ray rayIndex0(Point(-1, 3.1, 1.1), Vec(1.0, 0.1, 0.1));
    hit = vWorld->intersectTopLevel(stack, rayIndex0, v0x, v0y, v0z);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack[0] == 3);
    CPPUNIT_ASSERT(stack[1] == 0);
    CPPUNIT_ASSERT(stack[2] == 1);
    CPPUNIT_ASSERT(stack[3] == 1);
    CPPUNIT_ASSERT(roughlyEqual(v0y, 3.2));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 1.2));

    Ray rayIndex5(Point(6, -1, 7), Vec(0, 1, 0));
    hit = vWorld->intersectTopLevel(stack, rayIndex5, v0x, v0y, v0z);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack[0] == 3);
    CPPUNIT_ASSERT(stack[1] == 5);
    CPPUNIT_ASSERT(stack[2] == 2);
    CPPUNIT_ASSERT(stack[3] == 2);
    CPPUNIT_ASSERT(roughlyEqual(v0x, 6));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 7));

    Ray rayIndex6(Point(-1, 6, 7), Vec(1, 0, 0));
    hit = vWorld->intersectTopLevel(stack, rayIndex6, v0x, v0y, v0z);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack[0] == 3);
    CPPUNIT_ASSERT(stack[1] == 6);
    CPPUNIT_ASSERT(stack[2] == 1);
    CPPUNIT_ASSERT(stack[3] == 1);
    CPPUNIT_ASSERT(roughlyEqual(v0y, 6));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 7));

    Ray rayIndex7(Point(6, 9, 7), Vec(-1, -1, 0));
    hit = vWorld->intersectTopLevel(stack, rayIndex7, v0x, v0y, v0z);
    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(stack[0] == 3);
    CPPUNIT_ASSERT(stack[1] == 7);
    CPPUNIT_ASSERT(stack[2] == 10);
    CPPUNIT_ASSERT(stack[3] == 9);
    CPPUNIT_ASSERT(roughlyEqual(v0x, 5));
    CPPUNIT_ASSERT(roughlyEqual(v0z, 7));
}

CppUnit::Test* TestVoxelWorld::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Voxel World Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test voxel world", &TestVoxelWorld::testVoxelWorldInitialization));

    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test top-level intersection", &TestVoxelWorld::testTopLevelIntersection));

    return testSuite;
}