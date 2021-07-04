#include "TestIntersection.h"

void TestIntersection::setUp() {
    obj1 = new Object();
}

void TestIntersection::tearDown() {
    delete obj1;
}

void TestIntersection::testIntersection() {
    Intersection i1(1.5, obj1);

    CPPUNIT_ASSERT(i1.getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(i1.getT(), 1.5));
}

CppUnit::Test* TestIntersection::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Intersection Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestIntersection>("Test Intersection", &TestIntersection::testIntersection));

    return testSuite;
}