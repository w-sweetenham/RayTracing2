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

CppUnit::Test* TestTSphere::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Sphere Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestTSphere>("Test Sphere", &TestTSphere::testSphere));
    testSuite->addTest(new CppUnit::TestCaller<TestTSphere>("Test Sphere Copy", &TestTSphere::testSphereCopy));
    //testSuite->addTest(new CppUnit::TestCaller<TestSphere>("Test Sphere Intersection", &TestSphere::testSphereIntersection));
    //testSuite->addTest(new CppUnit::TestCaller<TestSphere>("Test Sphere transform", &TestSphere::testSphereTransform));
    //testSuite->addTest(new CppUnit::TestCaller<TestSphere>("Test Sphere normal", &TestSphere::testNormal));

    return testSuite;
}