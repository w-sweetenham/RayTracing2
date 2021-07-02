#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Matrix.h"
#include "src/basicConstructs/Ray.h"
#include "src/utils/Utils.h"

class TestRay : public CppUnit::TestFixture {
    private:
    Point* p1;
    Vec* v1;

    public:
    void setUp();
    void tearDown();

    void testRay();
    void testRoughlyEqual();
    void testPosition();
    void testTransform();
    void testTransformInPlace();

    static CppUnit::Test *suite();
};