#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/camera/Camera.h"
#include "src/basicConstructs/Colour.h"

class TestCamera : public CppUnit::TestFixture {
    private:

    public:
    void setUp();
    void tearDown();

    void testCamera();

    void testGetRay();

    static CppUnit::Test *suite();
};