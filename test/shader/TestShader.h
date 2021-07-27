#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/shader/Shader.h"
#include "src/basicConstructs/Colour.h"
#include "src/world/lightSource/PointLight.h"
#include "src/world/object/Object.h"
#include "src/world/object/material/Material.h"

class TestShader : public CppUnit::TestFixture {
    private:
    World* world;

    public:
    void setUp();
    void tearDown();

    void testPhongShader();

    static CppUnit::Test *suite();
};