#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/geometry/Tuple.h"
#include "src/geometry/Matrix.h"
#include "src/utils/Utils.h"

class TestMatrix : public CppUnit::TestFixture {
    private:
    Point* p1;
    Vec* v1;

    public:
    void setUp();
    void tearDown();

    void testIdentity();
    void testTranslation();
    void testScaling();
    void testRotation();
    void testShear();
    
    void testMatMatMultiply();
    void testTranspose();

    void testDet3D();
    void testSubMat4D();
    void testInverse();

    static CppUnit::Test *suite();
};