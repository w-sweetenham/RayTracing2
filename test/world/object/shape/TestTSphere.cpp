#include "TestTSphere.h"

void TestTSphere::setUp() {}

void TestTSphere::tearDown() {}

void TestTSphere::testSphere() {
    TSphere s1;
    float identityMatElems[16] = {1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1};
    Matrix mat1 = s1.getMat();
    Matrix invMat1 = s1.getInvMat();
    Matrix transInvMat1 = s1.getTransInvMat();
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(mat1.getElem(row, col), identityMatElems[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(invMat1.getElem(row, col), identityMatElems[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(transInvMat1.getElem(row, col), identityMatElems[(row*4) + col]));
        }
    }

    TSphere s2(TranslationMat(2, 1, 1));
    float matElems2[16] = {1, 0, 0, 2,
                           0, 1, 0, 1, 
                           0, 0, 1, 1, 
                           0, 0, 0, 1};
    float invMatElems2[16] = {1, 0, 0, -2,
                              0, 1, 0, -1, 
                              0, 0, 1, -1, 
                              0, 0, 0, 1};
    float transInvMatElems2[16] = {1, 0, 0, 0,
                                   0, 1, 0, 0, 
                                   0, 0, 1, 0, 
                                   -2, -1, -1, 1};
    Matrix mat2 = s2.getMat();
    Matrix invMat2 = s2.getInvMat();
    Matrix transInvMat2 = s2.getTransInvMat();
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(mat2.getElem(row, col), matElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(invMat2.getElem(row, col), invMatElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(transInvMat2.getElem(row, col), transInvMatElems2[(row*4) + col]));
        }
    }
}

void TestTSphere::testSphereCopy() {
    TSphere s1(TranslationMat(2, 1, 1));

    TSphere s2 = s1;
    float matElems2[16] = {1, 0, 0, 2, 
                           0, 1, 0, 1, 
                           0, 0, 1, 1, 
                           0, 0, 0, 1};
    float invMatElems2[16] = {1, 0, 0, -2, 
                              0, 1, 0, -1, 
                              0, 0, 1, -1, 
                              0, 0, 0, 1};
    float transInvMatElems2[16] = {1, 0, 0, 0, 
                                   0, 1, 0, 0, 
                                   0, 0, 1, 0, 
                                   -2, -1, -1, 1};

    Matrix mat2 = s2.getMat();
    Matrix invMat2 = s2.getInvMat();
    Matrix transInvMat2 = s2.getTransInvMat();

    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(mat2.getElem(row, col), matElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(invMat2.getElem(row, col), invMatElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(transInvMat2.getElem(row, col), transInvMatElems2[(row*4) + col]));
        }
    }
}

void TestTSphere::testTSphereIntersection() {
    TSphere s(TranslationMat(2, 1, 0));
    const Object* obj1;
    const Object* obj2;

    Ray r1(Point(0, 1, 0), Vec(1, 0, 0));
    Ray r2(Point(0, -1, 0), Vec(1, 0, 0));
    Ray r3(Point(2, 3, 0), Vec(0, -2, 0));

    IntersectionSet intSet;

    s.intersection(r1, intSet, obj1);
    s.intersection(r2, intSet, obj1);
    s.intersection(r3, intSet, obj2);

    CPPUNIT_ASSERT(intSet.getNumPosIntersections() == 4);
    CPPUNIT_ASSERT(intSet.getNumNegIntersections() == 0);
    CPPUNIT_ASSERT(intSet.getPosIntersection(0).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(0).getT(), 3));
    CPPUNIT_ASSERT(intSet.getPosIntersection(1).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(1).getT(), 1));
    CPPUNIT_ASSERT(intSet.getPosIntersection(2).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(2).getT(), 1.5));
    CPPUNIT_ASSERT(intSet.getPosIntersection(3).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(3).getT(), 0.5));
}

CppUnit::Test* TestTSphere::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Sphere Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestTSphere>("Test Sphere", &TestTSphere::testSphere));
    testSuite->addTest(new CppUnit::TestCaller<TestTSphere>("Test Sphere Copy", &TestTSphere::testSphereCopy));
    testSuite->addTest(new CppUnit::TestCaller<TestTSphere>("Test Sphere Intersection", &TestTSphere::testTSphereIntersection));
    //testSuite->addTest(new CppUnit::TestCaller<TestSphere>("Test Sphere transform", &TestSphere::testSphereTransform));
    //testSuite->addTest(new CppUnit::TestCaller<TestSphere>("Test Sphere normal", &TestSphere::testNormal));

    return testSuite;
}