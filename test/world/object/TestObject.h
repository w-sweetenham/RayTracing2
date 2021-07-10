#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/utils/Utils.h"
#include "src/world/object/Object.h"
#include "src/world/object/shape/TSphere.h"

class TestObject : public CppUnit::TestFixture {
    Object* obj1;
    TSphere* s;
    public:
    void setUp();
    void tearDown();

    void testObject();

    static CppUnit::Test *suite();
};