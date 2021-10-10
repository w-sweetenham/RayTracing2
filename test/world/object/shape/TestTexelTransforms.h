#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/world/object/shape/TexelTransform.h"
#include "src/basicConstructs/Tuple.h"

class TestTexelTransforms : public CppUnit::TestFixture {
    public:
    void setUp();
    void tearDown();

    void testCubeTransforms();

    static CppUnit::Test *suite();
};