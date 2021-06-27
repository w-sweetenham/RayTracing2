#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Colour.h"
#include "src/scene/world/object/material/Material.h"
#include "src/utils/Utils.h"

class TestMaterial : public CppUnit::TestFixture {
    private:

    public:
    void setUp();
    void tearDown();

    void testMaterial();

    static CppUnit::Test *suite();
};