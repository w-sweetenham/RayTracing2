#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Utils.h"
#include "src/world/object/Intersection.h"
#include "src/world/object/Object.h"

class TestIntersection : public CppUnit::TestFixture {
    Object* obj1;
    Object* obj2;
    Object* defaultObj;
    public:
    void setUp();
    void tearDown();

    void testIntersection();
    void testIntersectionComparison();

    void testIntersectionSet();
    void testIntersectionHit();

    static CppUnit::Test *suite();
};