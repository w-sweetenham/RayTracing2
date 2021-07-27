#include "TestShader.h"

void TestShader::setUp()
{
    world = new World(PointLight(Point(-2, 1, 0), Colour(1, 1, 1)));
    world->addMaterial(Material(0.1, 0.5, 0.7, 100, Colour(0.2, 0.4, 0.6)));
    world->addObject(TSphere(), 0);
}

void TestShader::tearDown()
{
    delete world;
}

void TestShader::testPhongShader() {
    Ray r(Point(-2, -1, 0), Vec(1, 1, 0));
    PhongShader shader;
    Colour c = shader.getColour(r, *world);
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.7907106, 0.8814212, 0.9721318)));
}

CppUnit::Test* TestShader::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Shader Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestShader>("Test canvas", &TestShader::testPhongShader));

    return testSuite;
}