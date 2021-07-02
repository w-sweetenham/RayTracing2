#include "TestColour.h"

void TestColour::setUp()
{
    c1 = new Colour(1.0, 0.5, 0.2);
    c2 = new Colour(0.5, 1.0, 0.3);
}

void TestColour::tearDown()
{
    delete c1;
    delete c2;
}

void TestColour::testColour() {
    CPPUNIT_ASSERT(roughlyEqual(c1->getRed(), 1.0));
    CPPUNIT_ASSERT(roughlyEqual(c1->getGreen(), 0.5));
    CPPUNIT_ASSERT(roughlyEqual(c1->getBlue(), 0.2));
}

void TestColour::testRoughlyEqual() {
    CPPUNIT_ASSERT(c1->roughlyEqual(Colour(1, 0.5, 0.2)));
    CPPUNIT_ASSERT(!(c1->roughlyEqual(Colour(1, 0.6, 0.1))));
}

void TestColour::testAddition() {
    Colour c3 = *c1 + *c2;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(1.5, 1.5, 0.5)));
}

void TestColour::testAdditionInPlace() {
    Colour c3 = *c1;
    c3 += *c2;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(1.5, 1.5, 0.5)));
}

void TestColour::testSubtraction() {
    Colour c3 = *c2 - *c1;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(-0.5, 0.5, 0.1)));
}

void TestColour::testSubtractionInPlace() {
    Colour c3 = *c2;
    c3 -= *c1;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(-0.5, 0.5, 0.1)));
}

void TestColour::testHadamard() {
    Colour c3 = *c1 * *c2;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(0.5, 0.5, 0.06)));
}

void TestColour::testScalarMultiplication() {
    Colour c3 = *c1 * 2.0;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(2, 1 , 0.4)));
}

void TestColour::testScalarMultiplicationInPlace() {
    Colour c3(1.0, 2.0, 3.0);
    c3 *= 2.0;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(2, 4, 6)));
}

void TestColour::testScalarDivision() {
    Colour c3 = *c1 / 2.0;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(0.5, 0.25, 0.1)));
}

void TestColour::testScalarDivisionInPlace() {
    Colour c3(1.0, 2.0, 3.0);
    c3 /= 2.0;
    CPPUNIT_ASSERT(c3.roughlyEqual(Colour(0.5, 1, 1.5)));
}

CppUnit::Test* TestColour::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Colour Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test colour", &TestColour::testColour));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test rough equals", &TestColour::testRoughlyEqual));

    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test addition", &TestColour::testAddition));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test addition in place", &TestColour::testAdditionInPlace));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test subtraction", &TestColour::testSubtraction));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test subtraction in place", &TestColour::testSubtractionInPlace));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test hadamard", &TestColour::testHadamard));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test scalar multiplication", &TestColour::testScalarMultiplication));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test scalar multiplication in place", &TestColour::testScalarMultiplicationInPlace));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test scalar division", &TestColour::testScalarDivision));
    testSuite->addTest(new CppUnit::TestCaller<TestColour>("Test scalar division in place", &TestColour::testScalarDivisionInPlace));

    return testSuite;
}