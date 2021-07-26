#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/camera/Canvas.h"
#include "src/basicConstructs/Colour.h"

class TestCanvas : public CppUnit::TestFixture {
    private:

    public:
    void setUp();
    void tearDown();

    void testCanvas();

    static CppUnit::Test *suite();
};