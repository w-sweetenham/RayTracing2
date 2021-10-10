#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Utils.h"
#include "src/basicConstructs/Matrix.h"
#include "src/world/object/Object.h"
#include "src/world/object/shape/TSphere.h"
#include "src/basicConstructs/Ray.h"
#include "src/world/object/Intersection.h"
#include "src/world/object/material/Material.h"

class TestObject : public CppUnit::TestFixture {
    Object* obj1;
    Material* m;
    public:
    void setUp();
    void tearDown();

    void testObject();

    void testIntersection();

    void testNormal();

    void testGetTexel();

    static CppUnit::Test *suite();
};