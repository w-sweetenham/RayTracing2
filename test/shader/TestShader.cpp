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
    Ray r1(Point(-2, -1, 0), Vec(1, 1, 0));
    Ray r2(Point(2, -1, 0), Vec(-1, 1, 0));
    Ray r3(Point(2, -2, 0), Vec(-1, 0, 0));
    PhongShader shader;
    Colour c = shader.getColour(r1, *world);
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.7907106, 0.8814212, 0.9721318)));
    c = shader.getColour(r2, *world);
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.02, 0.04, 0.06)));
    c = shader.getColour(r3, *world);
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0, 0, 0)));
}

void TestShader::testSchlick() {
    float testVal = schlick(1, 1, 1.5);
    CPPUNIT_ASSERT(roughlyEqual(testVal, 0.0597076));

    testVal = schlick(0.6, 1.5, 1);
    CPPUNIT_ASSERT(roughlyEqual(testVal, 0.04015606));

    testVal = schlick(1, 1.5, 1);
    CPPUNIT_ASSERT(roughlyEqual(testVal, 1.0));
}

CppUnit::Test* TestShader::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Shader Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestShader>("Test Phong Shader", &TestShader::testPhongShader));
    testSuite->addTest(new CppUnit::TestCaller<TestShader>("Test Schlick", &TestShader::testSchlick));

    return testSuite;
}