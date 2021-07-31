#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/object/shape/Cube.h"
#include "src/utils/Utils.h"
#include "src/world/object/Object.h"
#include "src/world/object/Intersection.h"

class TestCube : public CppUnit::TestFixture {
    public:
    void setUp();
    void tearDown();

    void testCube();
    void testCubeCopy();
    void testCubeIntersection();

    void testNormal();

    static CppUnit::Test *suite();
};