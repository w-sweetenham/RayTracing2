#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/world/World.h"
#include "src/world/lightSource/PointLight.h"
#include "src/world/object/material/Material.h"
#include "src/world/object/shape/TSphere.h"
#include "src/utils/Utils.h"
#include "src/basicConstructs/Matrix.h"

class TestWorld : public CppUnit::TestFixture {
    private:

    public:
    void setUp();
    void tearDown();

    void testWorld();

    void testAddObject();
    void testIntersection();
    void testShadow();

    static CppUnit::Test *suite();
};