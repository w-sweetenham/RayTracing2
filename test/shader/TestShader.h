#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "src/shader/Shader.h"
#include "src/basicConstructs/Colour.h"
#include "src/world/lightSource/PointLight.h"
#include "src/world/object/Object.h"
#include "src/world/object/material/Material.h"

//random comment

class TestShader : public CppUnit::TestFixture {
    private:
    World* world;
    World* world2;

    public:
    void setUp();
    void tearDown();

    void testPhongShader();

    void testReflection();

    void testRefraction();

    void testSchlick();

    static CppUnit::Test *suite();
};
