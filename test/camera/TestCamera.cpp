#include "TestCamera.h"

void TestCamera::setUp()
{}

void TestCamera::tearDown()
{}

void TestCamera::testCamera() {
    Camera cam(Point(0, 0, 0), Vec(2, 0, 0), Vec(0, 3, 0), 2, 3, 0.1, 0.01);

    CPPUNIT_ASSERT(cam.getOrigin().roughlyEqual(Point(0, 0, 0)));
    CPPUNIT_ASSERT(cam.getX().roughlyEqual(Vec(0, 0, -1)));
    CPPUNIT_ASSERT(cam.getY().roughlyEqual(Vec(0, 1, 0)));
    CPPUNIT_ASSERT(cam.getZ().roughlyEqual(Vec(1, 0, 0)));
}

void TestCamera::testGetRay() {
    Camera cam(Point(0, 0, 0), Vec(0, 0, 1), Vec(0, 1, 0), 2, 3, 0.1, 0.01);
    
    Ray r1 = cam.getRay(0, 0);
    CPPUNIT_ASSERT(r1.getOrigin().roughlyEqual(Point(0 ,0, 0)));
    CPPUNIT_ASSERT(r1.getDirection().roughlyEqual(Vec(0.1, 0.005, 0.015)));
    
    Ray r2 = cam.getRay(1, 1);
    CPPUNIT_ASSERT(r2.getOrigin().roughlyEqual(Point(0 ,0, 0)));
    CPPUNIT_ASSERT(r2.getDirection().roughlyEqual(Vec(0.1, -0.005, 0)));
    
    Ray r3 = cam.getRay(0, 2);
    CPPUNIT_ASSERT(r3.getOrigin().roughlyEqual(Point(0 ,0, 0)));
    CPPUNIT_ASSERT(r3.getDirection().roughlyEqual(Vec(0.1, 0.005, -0.015)));
}

CppUnit::Test* TestCamera::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Canvas Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestCamera>("Test camera", &TestCamera::testCamera));

    return testSuite;
}