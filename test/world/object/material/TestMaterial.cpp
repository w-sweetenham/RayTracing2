#include "TestMaterial.h"

void TestMaterial::setUp() {}

void TestMaterial::tearDown() {}

void TestMaterial::testMaterial() {
    Material material(0.1, 0.8, 0.9, 100, Colour(0.2, 0.4, 0.6));
    CPPUNIT_ASSERT(roughlyEqual(material.getAmbient(), 0.1));
    CPPUNIT_ASSERT(roughlyEqual(material.getDiffuse(), 0.8));
    CPPUNIT_ASSERT(roughlyEqual(material.getSpecular(), 0.9));
    CPPUNIT_ASSERT(roughlyEqual(material.getShininess(), 100));
    CPPUNIT_ASSERT(material.getColour().roughlyEqual(Colour(0.2, 0.4, 0.6)));

    Material material1(0.1, 0.8, 0.9, 100, Colour(0.2, 0.4, 0.6), 0.1, 0.2, 0.3);
    CPPUNIT_ASSERT(roughlyEqual(material1.getAmbient(), 0.1));
    CPPUNIT_ASSERT(roughlyEqual(material1.getDiffuse(), 0.8));
    CPPUNIT_ASSERT(roughlyEqual(material1.getSpecular(), 0.9));
    CPPUNIT_ASSERT(roughlyEqual(material1.getShininess(), 100));
    CPPUNIT_ASSERT(material1.getColour().roughlyEqual(Colour(0.2, 0.4, 0.6)));
    CPPUNIT_ASSERT(roughlyEqual(material1.getRefractiveIndex(), 0.1));
    CPPUNIT_ASSERT(roughlyEqual(material1.getReflectivity(), 0.2));
    CPPUNIT_ASSERT(roughlyEqual(material1.getTransparency(), 0.3));
}

CppUnit::Test* TestMaterial::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Material Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestMaterial>("Test material", &TestMaterial::testMaterial));

    return testSuite;
}