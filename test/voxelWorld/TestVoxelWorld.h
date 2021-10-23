#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/voxelWorld/VoxelWorld.h"

class TestVoxelWorld : public CppUnit::TestFixture {
    private:

    public:
    void setUp();
    void tearDown();

    void testVoxelWorldInitialization();

    static CppUnit::Test *suite();
};