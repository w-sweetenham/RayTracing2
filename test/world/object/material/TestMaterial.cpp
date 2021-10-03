#include "TestMaterial.h"

void TestMaterial::setUp() {}

void TestMaterial::tearDown() {}

void TestMaterial::testMaterial() {
    float ambient, diffuse, specular, shininess, reflectivity, refractiveIndex, transparency;
    Material* material1 = new basicMaterial(0.1, 0.2, 0.3, 100, Colour(0.5, 0.6, 0.7));
    material1->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(1, 1, 0));
    reflectivity = material1->getReflectivity();
    refractiveIndex = material1->getRefractiveIndex();
    transparency = material1->getTransparency();
    CPPUNIT_ASSERT(roughlyEqual(ambient, 0.1));
    CPPUNIT_ASSERT(roughlyEqual(diffuse, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(specular, 0.3));
    CPPUNIT_ASSERT(roughlyEqual(shininess, 100));
    Colour c = material1->getColour(Point(1, 4, 2));
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.5, 0.6, 0.7)));
    CPPUNIT_ASSERT(roughlyEqual(reflectivity, 0));
    CPPUNIT_ASSERT(roughlyEqual(transparency, 0));
    CPPUNIT_ASSERT(roughlyEqual(refractiveIndex, 1));

    Material* material2 = new basicMaterial(0.1, 0.8, 0.9, 100, Colour(0.2, 0.4, 0.6), 0.1, 0.2, 0.3);
    material2->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(1, 1, 0));
    c = material2->getColour(Point(3, 1, 7));
    reflectivity = material2->getReflectivity();
    refractiveIndex = material2->getRefractiveIndex();
    transparency = material2->getTransparency();
    CPPUNIT_ASSERT(roughlyEqual(ambient, 0.1));
    CPPUNIT_ASSERT(roughlyEqual(diffuse, 0.8));
    CPPUNIT_ASSERT(roughlyEqual(specular, 0.9));
    CPPUNIT_ASSERT(roughlyEqual(shininess, 100));
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.2, 0.4, 0.6)));
    CPPUNIT_ASSERT(roughlyEqual(refractiveIndex, 0.1));
    CPPUNIT_ASSERT(roughlyEqual(reflectivity, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(transparency, 0.3));
}

CppUnit::Test* TestMaterial::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Material Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestMaterial>("Test material", &TestMaterial::testMaterial));

    return testSuite;
}