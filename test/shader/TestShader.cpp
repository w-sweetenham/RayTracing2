#include "TestShader.h"

void TestShader::setUp()
{
    world = new World(PointLight(Point(-2, 1, 0), Colour(1, 1, 1)));
    world->addObject(TSphere(), basicMaterial(0.1, 0.5, 0.7, 100, Colour(0.2, 0.4, 0.6)));

    world2 = new World(PointLight(Point(0, 0, 0), Colour(1, 1, 1)));
    world2->addObject(Cube(TranslationMat(0, -2, 0)), basicMaterial(0.2, 0, 0, 0, Colour(0.1, 0.2, 0.3), 1.5, 0.8, 0.6));
    world2->addObject(TSphere(TranslationMat(0.31235, -2, 0)*ScalingMat(0.1, 0.1, 0.1)), basicMaterial(0.5, 0, 0, 0, Colour(0.2, 0.3, 0.1), 1.2, 0.5, 0.4));
    world2->addObject(TSphere(TranslationMat(1, 1, 0)*ScalingMat(0.1, 0.1, 0.1)), basicMaterial(0.1, 0, 0, 0, Colour(0.3, 0.1, 0.2), 1.2, 0.5, 0.4));
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

    Ray r4(Point(-1, 1, 0), Vec(1, -2, 0));
    c = shader.getColour(r4, *world2, 1);
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.07855954675, 0.1267189676, 0.089439824)));
}

void TestShader::testReflection() {
    Ray r(Point(-1, 1, 0), Vec(1, -2, 0));
    IntersectionSpec intSpec = world2->getIntersection(r);
    PhongShader shader;
    Colour testVal = shader.getReflectedColour(r, intSpec, *world2, 1);
    CPPUNIT_ASSERT(testVal.roughlyEqual(Colour(0.024, 0.008, 0.016)));
}

void TestShader::testRefraction() {
    Ray r(Point(-1, 1, 0), Vec(1, -2, 0));
    IntersectionSpec intSpec = world2->getIntersection(r);
    PhongShader shader;
    Colour testVal = shader.getRefractedColour(r, intSpec, *world2, 1);
    CPPUNIT_ASSERT(testVal.roughlyEqual(Colour(0.06, 0.09, 0.03)));
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
    testSuite->addTest(new CppUnit::TestCaller<TestShader>("Test Reflection", &TestShader::testReflection));
    testSuite->addTest(new CppUnit::TestCaller<TestShader>("Test Refraction", &TestShader::testRefraction));
    testSuite->addTest(new CppUnit::TestCaller<TestShader>("Test Schlick", &TestShader::testSchlick));

    return testSuite;
}