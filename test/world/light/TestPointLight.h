#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/basicConstructs/Colour.h"
#include "src/basicConstructs/Tuple.h"
#include "src/world/lightSource/PointLight.h"

class TestPointLight : public CppUnit::TestFixture {
    private:
    PointLight* l1;

    public:
    void setUp();
    void tearDown();

    void testPointLight();

    static CppUnit::Test *suite();
};