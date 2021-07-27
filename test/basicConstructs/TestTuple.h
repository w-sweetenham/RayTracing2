#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/basicConstructs/Tuple.h"
#include "src/utils/Utils.h"

class TestTuples : public CppUnit::TestFixture {
    private:
    Point* p1;
    Point* p2;
    Vec* v1;
    Vec* v2;

    public:
    void setUp();
    void tearDown();

    void testVec();
    void testVecCopy();
    void testVecAssignment();
    void testVecRoughEqual();
    void testPoint();
    void testPointCopy();
    void testPointAssignment();
    void testPointRoughEqual();

    void testVecVecAddition();
    void testPointVecAddition();
    void testPointVecAdditionInPlace();

    void testVecVecSubtraction();
    void testPointVecSubtraction();
    void testPointVecSubtractionInPlace();
    void testPointPointSubtraction();

    void testDot();
    void testCross();
    void testReflect();

    void testScalarMultiply();
    void testMagnitude();
    void testNormalize();

    static CppUnit::Test *suite();
};