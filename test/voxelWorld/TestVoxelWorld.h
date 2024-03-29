#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/voxelWorld/VoxelWorld.h"
#include "src/utils/Utils.h"

class TestVoxelWorld : public CppUnit::TestFixture {
    private:
    VoxelWorld* vWorld;
    public:
    void setUp();
    void tearDown();

    void testVoxelWorldInitialization();

    void testTopLevelIntersection();

    void testGetNextCube();

    void testGetChildCube();

    void testIntersect();

    void testGetIntersection();

    static CppUnit::Test *suite();
};