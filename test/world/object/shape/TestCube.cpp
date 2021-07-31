#include "TestCube.h"

void TestCube::setUp() {}

void TestCube::tearDown() {}

void TestCube::testCube() {
    Cube c1;
    float identityMatElems[16] = {1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1};
    Matrix mat1 = c1.getMat();
    Matrix invMat1 = c1.getInvMat();
    Matrix transInvMat1 = c1.getTransInvMat();
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(mat1.getElem(row, col), identityMatElems[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(invMat1.getElem(row, col), identityMatElems[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(transInvMat1.getElem(row, col), identityMatElems[(row*4) + col]));
        }
    }

    Cube c2(TranslationMat(2, 1, 1));
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
    Matrix mat2 = c2.getMat();
    Matrix invMat2 = c2.getInvMat();
    Matrix transInvMat2 = c2.getTransInvMat();
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(mat2.getElem(row, col), matElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(invMat2.getElem(row, col), invMatElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(transInvMat2.getElem(row, col), transInvMatElems2[(row*4) + col]));
        }
    }
}

void TestCube::testCubeCopy() {
    Cube c1(TranslationMat(2, 1, 1));

    Cube c2 = c1;
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

    Matrix mat2 = c2.getMat();
    Matrix invMat2 = c2.getInvMat();
    Matrix transInvMat2 = c2.getTransInvMat();

    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(mat2.getElem(row, col), matElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(invMat2.getElem(row, col), invMatElems2[(row*4) + col]));
            CPPUNIT_ASSERT(roughlyEqual(transInvMat2.getElem(row, col), transInvMatElems2[(row*4) + col]));
        }
    }
}

void TestCube::testCubeIntersection() {
    Cube c;
    const Object* obj1;
    const Object* obj2;

    Ray r1(Point(1, 2, 0), Vec(-1, -1, 0));
    Ray r2(Point(2, -1, 0), Vec(-1, 1, 0));
    Ray r3(Point(0, -2, 0), Vec(0, 1, 0));
    Ray r4(Point(-2, 1, 0), Vec(1, -1, 0));
    Ray r5(Point(-3, 0, 0), Vec(1, 1, 0));
    Ray r6(Point(2, 0, 0), Vec(1, 0, 0));

    IntersectionSet intSet;
    bool hit = false;

    hit = c.intersection(r1, intSet, obj1);
    CPPUNIT_ASSERT(hit == true);
    hit = c.intersection(r2, intSet, obj1);
    CPPUNIT_ASSERT(hit == true);
    hit = c.intersection(r3, intSet, obj2);
    CPPUNIT_ASSERT(hit == true);
    hit = c.intersection(r4, intSet, obj2);
    CPPUNIT_ASSERT(hit == true);
    hit = c.intersection(r5, intSet, obj2);
    CPPUNIT_ASSERT(hit == false);
    hit = c.intersection(r6, intSet, obj2);
    CPPUNIT_ASSERT(hit == true);

    CPPUNIT_ASSERT(intSet.getNumPosIntersections() == 8);
    CPPUNIT_ASSERT(intSet.getNumNegIntersections() == 2);
    CPPUNIT_ASSERT(intSet.getPosIntersection(0).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(0).getT(), 1));
    CPPUNIT_ASSERT(intSet.getPosIntersection(1).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(1).getT(), 2));
    CPPUNIT_ASSERT(intSet.getPosIntersection(2).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(2).getT(), 1));
    CPPUNIT_ASSERT(intSet.getPosIntersection(3).getObj() == obj1);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(3).getT(), 2));
    CPPUNIT_ASSERT(intSet.getPosIntersection(4).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(4).getT(), 1));
    CPPUNIT_ASSERT(intSet.getPosIntersection(5).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(5).getT(), 3));
    CPPUNIT_ASSERT(intSet.getPosIntersection(6).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(6).getT(), 1));
    CPPUNIT_ASSERT(intSet.getPosIntersection(7).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getPosIntersection(7).getT(), 2));

    CPPUNIT_ASSERT(intSet.getNegIntersection(0).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getNegIntersection(0).getT(), -3));
    CPPUNIT_ASSERT(intSet.getNegIntersection(1).getObj() == obj2);
    CPPUNIT_ASSERT(roughlyEqual(intSet.getNegIntersection(1).getT(), -1));
}

void TestCube::testNormal() {
    Cube c(TranslationMat(2, 1, 0));
    Vec norm1 = c.getNorm(Point(2, 2, -0.5));
    Vec norm2 = c.getNorm(Point(3, 1, 0.5));
    Vec norm3 = c.getNorm(Point(2, 1, -1));
    Vec norm4 = c.getNorm(Point(1.5, 0.5, 1));
    Vec norm5 = c.getNorm(Point(1, 1, 0));
    CPPUNIT_ASSERT(norm1.roughlyEqual(Vec(0, 1, 0)));
    CPPUNIT_ASSERT(norm2.roughlyEqual(Vec(1, 0, 0)));
    CPPUNIT_ASSERT(norm3.roughlyEqual(Vec(0, 0, -1)));
    CPPUNIT_ASSERT(norm4.roughlyEqual(Vec(0, 0, 1)));
    CPPUNIT_ASSERT(norm5.roughlyEqual(Vec(-1, 0, 0)));
}


CppUnit::Test* TestCube::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Cube Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestCube>("Test Cube", &TestCube::testCube));
    testSuite->addTest(new CppUnit::TestCaller<TestCube>("Test Cube Copy", &TestCube::testCubeCopy));
    testSuite->addTest(new CppUnit::TestCaller<TestCube>("Test Cube Intersection", &TestCube::testCubeIntersection));
    testSuite->addTest(new CppUnit::TestCaller<TestCube>("Test Cube normal", &TestCube::testNormal));

    return testSuite;
}