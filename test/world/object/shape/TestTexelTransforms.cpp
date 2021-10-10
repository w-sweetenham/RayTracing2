#include "TestTexelTransforms.h"

void TestTexelTransforms::setUp() {}

void TestTexelTransforms::tearDown() {}

void TestTexelTransforms::testCubeTransforms() {
    CubeTransform ct1(2);
    /*
    front face
    */
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.3, -0.4, -1)).roughlyEqual(Point2D(0.35, 0.3)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.9, 0.7, -1)).roughlyEqual(Point2D(0.05, 0.85)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.9, 0.2, -1)).roughlyEqual(Point2D(0.95, 0.6)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.15, -0.95, -1)).roughlyEqual(Point2D(0.575, 0.025)));

    /*
    bottom face
    */
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.3, -1, 0.4)).roughlyEqual(Point2D(0.35, -0.7)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.9, -1, -0.7)).roughlyEqual(Point2D(0.05, -0.15)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.9, -1, -0.2)).roughlyEqual(Point2D(0.95, -0.4)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.15, -1, 0.95)).roughlyEqual(Point2D(0.575, -0.975)));

    /*
    top face
    */
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.3, 1, -0.4)).roughlyEqual(Point2D(0.35, 1.3)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.9, 1, 0.7)).roughlyEqual(Point2D(0.05, 1.85)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.9, 1, 0.2)).roughlyEqual(Point2D(0.95, 1.6)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.15, 1, -0.95)).roughlyEqual(Point2D(0.575, 1.025)));

    /*
    right face
    */
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(1, -0.4, -0.3)).roughlyEqual(Point2D(1.35, 0.3)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(1, 0.7, -0.9)).roughlyEqual(Point2D(1.05, 0.85)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(1, 0.2, 0.9)).roughlyEqual(Point2D(1.95, 0.6)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(1, -0.95, 0.15)).roughlyEqual(Point2D(1.575, 0.025)));

    /*
    left face
    */
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-1, -0.4, 0.3)).roughlyEqual(Point2D(-0.65, 0.3)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-1, 0.7, 0.9)).roughlyEqual(Point2D(-0.95, 0.85)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-1, 0.2, -0.9)).roughlyEqual(Point2D(-0.05, 0.6)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-1, -0.95, -0.15)).roughlyEqual(Point2D(-0.425, 0.025)));

    /*
    back face
    */
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.3, 0.4, 1)).roughlyEqual(Point2D(0.35, 2.3)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(-0.9, -0.7, 1)).roughlyEqual(Point2D(0.05, 2.85)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.9, -0.2, 1)).roughlyEqual(Point2D(0.95, 2.6)));
    CPPUNIT_ASSERT(ct1.get2DPoint(Point(0.15, 0.95, 1)).roughlyEqual(Point2D(0.575, 2.025)));

    CPPUNIT_ASSERT(ct1.getTexel(Point(0.15, 0.95, 1)).roughlyEqual(Point2D(1.15, 4.05)));
}


CppUnit::Test* TestTexelTransforms::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Texel Transform Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestTexelTransforms>("Test Texel Transforms", &TestTexelTransforms::testCubeTransforms));
    return testSuite;
}