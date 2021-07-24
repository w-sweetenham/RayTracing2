#include "TestPointLight.h"

void TestPointLight::setUp()
{
    l1 = new PointLight(Point(1, 1, 1), Colour(1.0, 0.5, 0.2));
}

void TestPointLight::tearDown()
{
    delete l1;
}

void TestPointLight::testPointLight() {
    Point origin = l1->getOrigin();
    Colour intensity = l1->getIntensity();
    CPPUNIT_ASSERT(origin.roughlyEqual(Point(1, 1, 1)));
    CPPUNIT_ASSERT(intensity.roughlyEqual(Colour(1, 0.5, 0.2)));
}

CppUnit::Test* TestPointLight::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Point Light Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestPointLight>("Test colour", &TestPointLight::testPointLight));

    return testSuite;
}