#include "TestObject.h"

void TestObject::setUp() {
    s = new TSphere();
    obj1 = new Object(s, "a");
}

void TestObject::tearDown() {
    delete obj1;
    delete s;
}

void TestObject::testObject() {
    CPPUNIT_ASSERT(obj1->getShape() == s);
    CPPUNIT_ASSERT(obj1->getMaterialName() == "a");
}

CppUnit::Test* TestObject::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Object Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestObject>("Test Object", &TestObject::testObject));

    return testSuite;
}