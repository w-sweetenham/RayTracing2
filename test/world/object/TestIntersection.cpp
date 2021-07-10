#include "TestIntersection.h"

void TestIntersection::setUp() {
    obj1 = new Object();
    obj2 = new Object();
}

void TestIntersection::tearDown() {
    delete obj1;
    delete obj2;
}

void TestIntersection::testIntersection() {
    Intersection i1(1.5, obj1);

    CPPUNIT_ASSERT(i1.getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(i1.getT(), 1.5));
}

void TestIntersection::testIntersectionComparison() {
    Intersection i1(1, obj1);
    Intersection i2(2, obj1);
    Intersection i3(-1.5, obj1);

    CPPUNIT_ASSERT(i1 < i2);
    CPPUNIT_ASSERT(i3 < i1);
}

void TestIntersection::testIntersectionSet() {
    IntersectionSet iSet;
    iSet.addIntersection(Intersection(2, obj1));
    iSet.addIntersection(Intersection(-0.5, obj2));
    iSet.addIntersection(Intersection(0.6, obj1));

    CPPUNIT_ASSERT(iSet.getNumPosIntersections() == 2);
    CPPUNIT_ASSERT(iSet.getNumNegIntersections() == 1);

    bool exceptionCaught = false;
    try {
        Intersection i1 = iSet.getPosIntersection(0);
        CPPUNIT_ASSERT(i1.getObj() == obj1);
        CPPUNIT_ASSERT(roughlyEqual(i1.getT(), 2));
        Intersection i2 = iSet.getPosIntersection(2);
    } catch(BadIndex b) {
        exceptionCaught = true;
    }
    CPPUNIT_ASSERT(exceptionCaught == true);

    exceptionCaught = false;
    try {
        Intersection i1 = iSet.getNegIntersection(0);
        CPPUNIT_ASSERT(i1.getObj() == obj2);
        CPPUNIT_ASSERT(roughlyEqual(i1.getT(), -0.5));
        Intersection i2 = iSet.getNegIntersection(1);
    } catch(BadIndex b) {
        exceptionCaught = true;
    }
    CPPUNIT_ASSERT(exceptionCaught == true);
}

void TestIntersection::testIntersectionHit() {
    IntersectionSet iSet;
    iSet.addIntersection(Intersection(2, obj1));
    iSet.addIntersection(Intersection(-0.5, obj2));
    iSet.addIntersection(Intersection(0.6, obj1));

    Intersection intersection(0, NULL);
    bool hit = false;

    hit = iSet.getHit(intersection);

    CPPUNIT_ASSERT(hit == true);
    CPPUNIT_ASSERT(intersection.getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intersection.getT(), 0.6));
}

CppUnit::Test* TestIntersection::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Intersection Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestIntersection>("Test Intersection", &TestIntersection::testIntersection));
    testSuite->addTest(new CppUnit::TestCaller<TestIntersection>("Test Intersection Comparison", &TestIntersection::testIntersectionComparison));
    testSuite->addTest(new CppUnit::TestCaller<TestIntersection>("Test Intersection Set", &TestIntersection::testIntersectionSet));
    testSuite->addTest(new CppUnit::TestCaller<TestIntersection>("Test Intersection Set Hit", &TestIntersection::testIntersectionHit));

    return testSuite;
}