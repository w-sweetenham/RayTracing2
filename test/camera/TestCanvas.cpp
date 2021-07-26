#include "TestCanvas.h"

void TestCanvas::setUp()
{}

void TestCanvas::tearDown()
{}

void TestCanvas::testCanvas() {
    Canvas c1(2, 2);
    c1.setPixel(0, 0, Colour(0.1, 0.2, 0.3));
    c1.setPixel(1, 1, Colour(0.2, 0.4, 0.6));
    CPPUNIT_ASSERT(c1.getPixel(0, 0).roughlyEqual(Colour(0.1, 0.2, 0.3)));
    CPPUNIT_ASSERT(c1.getPixel(1, 1).roughlyEqual(Colour(0.2, 0.4, 0.6)));

    Canvas c2(2, 2, Colour(0.3, 0.4, 0.5));
    CPPUNIT_ASSERT(c2.getPixel(0, 1).roughlyEqual(Colour(0.3, 0.4, 0.5)));
    CPPUNIT_ASSERT(c2.getPixel(1, 0).roughlyEqual(Colour(0.3, 0.4, 0.5)));
}

CppUnit::Test* TestCanvas::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Canvas Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestCanvas>("Test canvas", &TestCanvas::testCanvas));

    return testSuite;
}