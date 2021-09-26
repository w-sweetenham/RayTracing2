#include "TestUtils.h"

void TestUtils::setUp()
{
    a1 = new float(1.000001);
    b1 = new float(1.0);

    a2 = new float(1.1);
    b2 = new float(1.0);
}

void TestUtils::tearDown()
{
    delete a1;
    delete b1;

    delete a2;
    delete b2;
}

void TestUtils::testRoughEqual()
{
    CPPUNIT_ASSERT(roughlyEqual(*a1, *b1));
    CPPUNIT_ASSERT(!roughlyEqual(*a2, *b2));
}

CppUnit::Test* TestUtils::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Utils Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestUtils>("test1", &TestUtils::testRoughEqual));
    return testSuite;
}