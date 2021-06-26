#include "test/geometry/TestTuple.h"

void TestTuples::setUp()
{
    v1 = new Vec(1.0, 1.0, 1.0);
    v2 = new Vec(2.0, 3.0, 4.0);
    p1 = new Point(3.0, 3.0, 3.0);
    p2 = new Point(4.0, 5.0, 6.0);
}

void TestTuples::tearDown()
{
    delete v1;
    delete v2;
    delete p1;
    delete p2;
}

void TestTuples::testVec()
{
    CPPUNIT_ASSERT(roughlyEqual(v1->getElem(0), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(v1->getElem(1), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(v1->getElem(2), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(v1->getElem(3), 0.0));
}

void TestTuples::testVecCopy()
{
    Vec v3 = *v2;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), 2.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testVecAssignment()
{
    Vec v3(7.0, 8.0, 9.0);
    v3 = *v2;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), 2.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testPoint()
{
    CPPUNIT_ASSERT(roughlyEqual(p1->getElem(0), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(p1->getElem(1), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(p1->getElem(2), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(p1->getElem(3), 1.0));
}

void TestTuples::testPointCopy()
{
    Point p3 = *p2;
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(0), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(1), 5.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(2), 6.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(3), 1.0));
}

void TestTuples::testPointAssignment()
{
    Point p3(7.0, 8.0, 9.0);
    p3 = *p2;
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(0), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(1), 5.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(2), 6.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(3), 1.0));
}

void TestTuples::testVecVecAddition()
{
    Vec v3 = *v1 + *v2;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), 5.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testPointVecAddition()
{
    Point p3 = *p2 + *v1;
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(0), 5.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(1), 6.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(2), 7.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(3), 1.0));
}

void TestTuples::testPointVecAdditionInPlace() {
    Point p3 = *p2;
    p3 += *v2;
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(0), 6.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(1), 8.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(2), 10.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(3), 1.0));
}

void TestTuples::testVecVecSubtraction()
{
    Vec v3 = *v1 - *v2;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), -1.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), -2.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), -3.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testPointVecSubtraction()
{
    Point p3 = *p2 - *v1;
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(0), 3.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(1), 4.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(2), 5.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(3), 1.0));
}

void TestTuples::testPointVecSubtractionInPlace() {
    Point p3 = *p2;
    p3 -= *v2;
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(0), 2.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(1), 2.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(2), 2.0));
    CPPUNIT_ASSERT(roughlyEqual(p3.getElem(3), 1.0));
}

void TestTuples::testPointPointSubtraction()
{
    Vec v3 = *p1 - *p2;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), -1.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), -2.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), -3.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testDot() {
    float prod = v1->dot(*v2);
    CPPUNIT_ASSERT(roughlyEqual(prod, 9.0));
}

void TestTuples::testCross() {
    Vec v3 = *v1 * *v2;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), -2.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testScalarMultiply()
{
    Vec v3 = *v2 * -1.0;
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), -2.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), -3.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), -4.0));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

void TestTuples::testMagnitude()
{
    float mag = v2->mag();
    CPPUNIT_ASSERT(roughlyEqual(mag, 5.385165));
}

void TestTuples::testNormalize()
{
    Vec v3 = *v2;
    v3.normalize();
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(0), 0.3713907));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(1), 0.557086));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(2), 0.74278135));
    CPPUNIT_ASSERT(roughlyEqual(v3.getElem(3), 0.0));
}

CppUnit::Test* TestTuples::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Matrix Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test vector", &TestTuples::testVec));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test vector copy", &TestTuples::testVecCopy));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test vector assignment", &TestTuples::testVecAssignment));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point", &TestTuples::testPoint));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point copy", &TestTuples::testPointCopy));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point assignment", &TestTuples::testPointAssignment));

    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test vector vector addition", &TestTuples::testVecVecAddition));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point vec addition", &TestTuples::testPointVecAddition));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point vec addition in place", &TestTuples::testPointVecAdditionInPlace));

    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test dot product", &TestTuples::testDot));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test cross product", &TestTuples::testCross));
    
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test vec vec subtraction", &TestTuples::testVecVecSubtraction));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point vec subtraction", &TestTuples::testPointVecSubtraction));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point vec subtraction in place", &TestTuples::testPointVecSubtractionInPlace));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test point point subtraction", &TestTuples::testPointPointSubtraction));

    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test vector scalar multiply", &TestTuples::testScalarMultiply));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test magnitude", &TestTuples::testMagnitude));
    testSuite->addTest(new CppUnit::TestCaller<TestTuples>("Test normalize", &TestTuples::testNormalize));

    return testSuite;
}