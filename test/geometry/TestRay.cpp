#include "TestRay.h"

void TestRay::setUp() {
    p1 = new Point(1.0, 2.0, 3.0);
    v1 = new Vec(2.0, 3.0, 4.0);
}

void TestRay::tearDown() {
    delete p1;
    delete v1;
}


void TestRay::testRay() {
    Ray ray(*p1, *v1);
    CPPUNIT_ASSERT(ray.getOrigin().roughlyEqual(Point(1, 2, 3)));
    CPPUNIT_ASSERT(ray.getDirection().roughlyEqual(Vec(2, 3, 4)));
}

void TestRay::testRoughlyEqual() {
    Ray ray(*p1, *v1);
    CPPUNIT_ASSERT(ray.roughlyEqual(Ray(Point(1, 2, 3), Vec(2, 3, 4))));
    CPPUNIT_ASSERT(!(ray.roughlyEqual(Ray(Point(1, 2.1, 3), Vec(2, 3.2, 4)))));
}

void TestRay::testPosition() {
    Ray ray(*p1, *v1);
    Point p2 = ray.getPosition(3.0);
    CPPUNIT_ASSERT(p2.roughlyEqual(Point(7, 11, 15)));
}

void TestRay::testTransform() {
    Ray ray(*p1, *v1);
    Ray transRay = ray.transform(ScalingMat(2, 2, 2));
    
    CPPUNIT_ASSERT(transRay.getOrigin().roughlyEqual(Point(2, 4, 6)));
    CPPUNIT_ASSERT(transRay.getDirection().roughlyEqual(Vec(4, 6, 8)));
}

void TestRay::testTransformInPlace() {
    Ray ray(*p1, *v1);
    ray.transformInPlace(ScalingMat(2, 2, 2));
    
    CPPUNIT_ASSERT(ray.getOrigin().roughlyEqual(Point(2, 4, 6)));
    CPPUNIT_ASSERT(ray.getDirection().roughlyEqual(Vec(4, 6, 8)));
}

CppUnit::Test* TestRay::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Ray Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestRay>("Test Ray", &TestRay::testRay));
    testSuite->addTest(new CppUnit::TestCaller<TestRay>("Test Roughly Equal", &TestRay::testRoughlyEqual));
    testSuite->addTest(new CppUnit::TestCaller<TestRay>("Test position", &TestRay::testPosition));
    testSuite->addTest(new CppUnit::TestCaller<TestRay>("Test transform", &TestRay::testTransform));
    testSuite->addTest(new CppUnit::TestCaller<TestRay>("Test transform in place", &TestRay::testTransformInPlace));

    return testSuite;
}