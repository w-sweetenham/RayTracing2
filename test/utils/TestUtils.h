#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Utils.h"

class TestUtils : public CppUnit::TestFixture {
    private:
    float* a1;
    float* b1;

    float* a2;
    float* b2;

    public:
    void setUp();
    void tearDown();
    void testRoughEqual();
    static CppUnit::Test *suite();
};