#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Utils.h"
#include "src/world/object/Intersection.h"
#include "src/world/object/Object.h"

class TestIntersection : public CppUnit::TestFixture {
    Object* obj1;
    public:
    void setUp();
    void tearDown();

    void testIntersection();

    static CppUnit::Test *suite();
};