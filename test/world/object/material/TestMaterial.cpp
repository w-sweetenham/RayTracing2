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
    Colour c = material1->getColour(Point2D(1, 4));
    CPPUNIT_ASSERT(c.roughlyEqual(Colour(0.5, 0.6, 0.7)));
    CPPUNIT_ASSERT(roughlyEqual(reflectivity, 0));
    CPPUNIT_ASSERT(roughlyEqual(transparency, 0));
    CPPUNIT_ASSERT(roughlyEqual(refractiveIndex, 1));

    Material* material2 = new basicMaterial(0.1, 0.8, 0.9, 100, Colour(0.2, 0.4, 0.6), 0.1, 0.2, 0.3);
    material2->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(1, 1, 0));
    c = material2->getColour(Point2D(3, 1));
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

void TestMaterial::testPatternMaterial() {
    Material* material1 = new PatternMaterial(0.2, 0.3, 0.5, 123, CheckerPattern(Colour(0.5, 0.5, 0.5), Colour(0.2, 0.2, 0.2)), 0.15, 0.25, 0.5);
    Material* material2 = material1->clone();//check copy constructor works
    float ambient, diffuse, specular, shininess, reflectivity, refractiveIndex, transparency;
    material2->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(1, 1, 1));
    reflectivity = material2->getReflectivity();
    refractiveIndex = material2->getRefractiveIndex();
    transparency = material2->getTransparency();
    CPPUNIT_ASSERT(roughlyEqual(ambient, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(diffuse, 0.3));
    CPPUNIT_ASSERT(roughlyEqual(specular, 0.5));
    CPPUNIT_ASSERT(roughlyEqual(shininess, 123));
    CPPUNIT_ASSERT(roughlyEqual(refractiveIndex, 0.15));
    CPPUNIT_ASSERT(roughlyEqual(reflectivity, 0.25));
    CPPUNIT_ASSERT(roughlyEqual(transparency, 0.5));
    CPPUNIT_ASSERT(material2->getColour(Point2D(0.5, 0.5)).roughlyEqual(Colour(0.5, 0.5, 0.5)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(0.5, -0.5)).roughlyEqual(Colour(0.2, 0.2, 0.2)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(-0.5, -0.5)).roughlyEqual(Colour(0.5, 0.5, 0.5)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(-0.5, 0.5)).roughlyEqual(Colour(0.2, 0.2, 0.2)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(1.5, -0.5)).roughlyEqual(Colour(0.5, 0.5, 0.5)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(1.5, -1.5)).roughlyEqual(Colour(0.2, 0.2, 0.2)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(-1.5, -1.5)).roughlyEqual(Colour(0.5, 0.5, 0.5)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(-0.5, -1.5)).roughlyEqual(Colour(0.2, 0.2, 0.2)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(-1.5, 0.5)).roughlyEqual(Colour(0.5, 0.5, 0.5)));
    CPPUNIT_ASSERT(material2->getColour(Point2D(-1.5, 1.5)).roughlyEqual(Colour(0.2, 0.2, 0.2)));
}

CppUnit::Test* TestMaterial::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Material Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestMaterial>("Test material", &TestMaterial::testMaterial));
    testSuite->addTest(new CppUnit::TestCaller<TestMaterial>("Test pattern material", &TestMaterial::testPatternMaterial));

    return testSuite;
}