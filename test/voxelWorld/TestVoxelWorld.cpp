#include "TestVoxelWorld.h"

void TestVoxelWorld::setUp() {}

void TestVoxelWorld::tearDown() {}

void TestVoxelWorld::testVoxelWorldInitialization() {
    /*
    * This test builds a voxel tree structure from an input array representing a cube of voxels each with their value stored as an unsigned char.
    * It goes through each scale of voxel cube and checks a set of indexes to make sure the correct values are set
    */
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
    VoxelWorld vWorld(voxelVals, 512);

    CPPUNIT_ASSERT(vWorld.getSideLengthPower() == 3);

    /*
     * scale 1 checks
     */

    CPPUNIT_ASSERT(vWorld.getVoxel(0) == 0);
    CPPUNIT_ASSERT(vWorld.getVoxel(8) == 0);
    CPPUNIT_ASSERT(vWorld.getVoxel(10) == 7);
    CPPUNIT_ASSERT(vWorld.getVoxel(457) == 0);
    CPPUNIT_ASSERT(vWorld.getVoxel(465) == 7);
    CPPUNIT_ASSERT(vWorld.getVoxel(458) == 7);

    /*
     * scale 2 checks
     */

    CPPUNIT_ASSERT(vWorld.getVoxel(512) == 14);
    CPPUNIT_ASSERT(vWorld.getVoxel(513) == 15);
    CPPUNIT_ASSERT(vWorld.getVoxel(514) == 15);
    CPPUNIT_ASSERT(vWorld.getVoxel(515) == 15);
    CPPUNIT_ASSERT(vWorld.getVoxel(516) == 238);
    CPPUNIT_ASSERT(vWorld.getVoxel(517) == 0);
    CPPUNIT_ASSERT(vWorld.getVoxel(518) == 255);
    CPPUNIT_ASSERT(vWorld.getVoxel(519) == 0);

    /*
     * scale 3 checks
     */
    CPPUNIT_ASSERT(vWorld.getVoxel(520) == 95);
}

CppUnit::Test* TestVoxelWorld::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Voxel World Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestVoxelWorld>("Test voxel world", &TestVoxelWorld::testVoxelWorldInitialization));

    return testSuite;
}