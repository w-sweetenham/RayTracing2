#include "TestMaterial.h"

void TestMaterial::setUp() {}

void TestMaterial::tearDown() {}

void TestMaterial::testMaterial() {
    Material material(0.1, 0.8, 0.9, Colour(0.2, 0.4, 0.6));
    CPPUNIT_ASSERT(roughlyEqual(material.getAmbient(), 0.1));
    CPPUNIT_ASSERT(roughlyEqual(material.getDiffuse(), 0.8));
    CPPUNIT_ASSERT(roughlyEqual(material.getSpecular(), 0.9));
    CPPUNIT_ASSERT(material.getColour().roughlyEqual(Colour(0.2, 0.4, 0.6)));
}

CppUnit::Test* TestMaterial::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Material Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestMaterial>("Test material", &TestMaterial::testMaterial));

    return testSuite;
}