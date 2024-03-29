#include "TestObject.h"

void TestObject::setUp() {
    obj1 = new Object(TSphere(TranslationMat(2, 1, 0)), basicMaterial(0.1, 0.2, 0.3, 100, Colour(0.2, 0.3, 0.4)));
}

void TestObject::tearDown() {
    delete obj1;
}

void TestObject::testObject() {
    float ambient, diffuse, specular, shininess;
    obj1->material->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(1, 1, 1));
    CPPUNIT_ASSERT(roughlyEqual(ambient, 0.1));
    CPPUNIT_ASSERT(roughlyEqual(diffuse, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(specular, 0.3));
    CPPUNIT_ASSERT(roughlyEqual(shininess, 100));
}

void TestObject::testIntersection() {
    Ray r1(Point(0, 1, 0), Vec(1, 0, 0));
    Ray r2(Point(0, -1, 0), Vec(1, 0, 0));
    Ray r3(Point(2, 3, 0), Vec(0, -2, 0));

    IntersectionSet intSet;

    obj1->intersect(r1, intSet);
    obj1->intersect(r2, intSet);
    obj1->intersect(r3, intSet);

    CPPUNIT_ASSERT(intSet.getNumPosIntersections() == 4);
    CPPUNIT_ASSERT(intSet.getNumNegIntersections() == 0);
    CPPUNIT_ASSERT(intSet.getPosIntersection(0).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(0).getT(), 3));
    CPPUNIT_ASSERT(intSet.getPosIntersection(1).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(1).getT(), 1));
    CPPUNIT_ASSERT(intSet.getPosIntersection(2).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(2).getT(), 1.5));
    CPPUNIT_ASSERT(intSet.getPosIntersection(3).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(3).getT(), 0.5));
}

void TestObject::testNormal() {
    Object obj(TSphere(TranslationMat(2, 0, 0)), basicMaterial(0.1, 0.2, 0.3, 100, Colour(0.2, 0.3, 0.4)));
    Vec norm = obj.getNorm(Point(2.7071068, 0.7071068, 0));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0.7071068, 0.7071068, 0)));
}

void TestObject::testGetTexel() {
    Object obj(Cube(TranslationMat(2, 0, 0), 2), PatternMaterial(0.1, 0.2, 0.3, 100, CheckerPattern(Colour(0.1, 0.1, 0.1), Colour(0.9, 0.9, 0.9)), 1.5, 0, 0));
    CPPUNIT_ASSERT(obj.getColour(Point(1.5, -0.5, -1)).roughlyEqual(Colour(0.1, 0.1, 0.1)));
    CPPUNIT_ASSERT(obj.getColour(Point(2.5, -0.5, -1)).roughlyEqual(Colour(0.9, 0.9, 0.9)));
    CPPUNIT_ASSERT(obj.getColour(Point(1.5, 0.5, -1)).roughlyEqual(Colour(0.9, 0.9, 0.9)));
    CPPUNIT_ASSERT(obj.getColour(Point(2.5, 0.5, -1)).roughlyEqual(Colour(0.1, 0.1, 0.1)));
}

CppUnit::Test* TestObject::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Object Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object", &TestObject::testObject));
    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object Intersection", &TestObject::testIntersection));

    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object normal", &TestObject::testNormal));

    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test get texel", &TestObject::testGetTexel));

    return testSuite;
}