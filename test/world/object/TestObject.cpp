#include "TestObject.h"

void TestObject::setUp() {
    m = new Material(0.1, 0.2, 0.3, Colour(0.2, 0.3, 0.4));
    s = new TSphere(TranslationMat(2, 1, 0));
    obj1 = new Object(s, m);
}

void TestObject::tearDown() {
    delete obj1;
    delete s;
}

void TestObject::testObject() {
    CPPUNIT_ASSERT(obj1->getShape() == s);
    CPPUNIT_ASSERT(obj1->getMaterial() == m);
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
    TSphere s(TranslationMat(2, 0, 0));
    Object obj(&s, m);
    Vec norm = obj.getNorm(Point(2.7071068, 0.7071068, 0));
    CPPUNIT_ASSERT(norm.roughlyEqual(Vec(0.7071068, 0.7071068, 0)));
}

CppUnit::Test* TestObject::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Object Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object", &TestObject::testObject));
    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object Intersection", &TestObject::testIntersection));

    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object normal", &TestObject::testNormal));

    return testSuite;
}