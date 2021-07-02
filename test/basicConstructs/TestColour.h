#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Colour.h"
#include "src/utils/Utils.h"

class TestColour : public CppUnit::TestFixture {
    private:
    Colour* c1;
    Colour* c2;

    public:
    void setUp();
    void tearDown();

    void testColour();
    void testRoughlyEqual();

    void testAddition();
    void testAdditionInPlace();
    void testSubtraction();
    void testSubtractionInPlace();
    void testHadamard();
    void testScalarMultiplication();
    void testScalarMultiplicationInPlace();
    void testScalarDivision();
    void testScalarDivisionInPlace();

    static CppUnit::Test *suite();
};