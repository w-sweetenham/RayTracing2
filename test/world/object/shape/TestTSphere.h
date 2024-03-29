#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/object/shape/TSphere.h"
#include "src/utils/Utils.h"
#include "src/world/object/Object.h"
#include "src/world/object/Intersection.h"

class TestTSphere : public CppUnit::TestFixture {
    public:
    void setUp();
    void tearDown();

    void testSphere();
    void testSphereCopy();
    void testTSphereIntersection();

    void testNormal();

    void testTexel();

    static CppUnit::Test *suite();
};