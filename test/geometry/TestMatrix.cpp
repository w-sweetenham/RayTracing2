#include "TestMatrix.h"

void TestMatrix::setUp() {
    p1 = new Point(1.0, 2.0, 3.0);
    v1 = new Vec(2.0, 3.0, 4.0);
}

void TestMatrix::tearDown() {
    delete p1;
    delete v1;
}


void TestMatrix::testIdentity() {
    IdentityMat mat;
    Point p2 = mat * (*p1);
    Vec v2 = mat * (*v1);

    CPPUNIT_ASSERT(p2.roughlyEqual(Point(1, 2, 3)));
    CPPUNIT_ASSERT(v2.roughlyEqual(Vec(2, 3, 4)));
}

void TestMatrix::testMatMatMultiply() {
    Matrix m1(1.0);
    Matrix m2(2.0);

    Matrix m3 = m1 * m2;

    float correctElems[16] = {8, 8, 8, 8, 
                              8, 8, 8, 8,
                              8, 8, 8, 8,
                              8, 8, 8, 8};

    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(m3.getElem(row, col), correctElems[(row*4)+col]));
        }
    }
}

void TestMatrix::testTranspose() {
    float elems[16] = {1.0, 2.0, 3.0, 4.0, 
                       5.0, 6.0, 7.0, 8.0, 
                       9.0, 10.0, 11.0, 12.0, 
                       13.0, 14.0, 15.0, 16.0};
    Matrix m3(elems);
    m3.transpose();

    float transposedElems[16] = {1, 5, 9, 13,
                                 2, 6, 10, 14,
                                 3, 7, 11, 15,
                                 4, 8, 12, 16};

    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            CPPUNIT_ASSERT(roughlyEqual(m3.getElem(row, col), transposedElems[(row*4)+col]));
        }
    }
}

void TestMatrix::testDet3D() {
    float elems[] = {1.0, 5.0, 9.0, 
                     7.0, 2.0, 2.0, 
                     1.0, 4.0, 3.0};
    CPPUNIT_ASSERT(roughlyEqual(det3D(elems), 137.0));
}

void TestMatrix::testSubMat4D() {
    float elems[16];
    float subMat[9];
    float correctSubMat[] = {1.0, 3.0, 4.0, 
                             9.0, 11.0, 12.0, 
                             13.0, 15.0, 16.0};

    for(int i=0; i<16; i++) {
        elems[i] = i+1;
    }

    getSubMat4D(elems, subMat, 1, 1);
    for(int i=0; i<9; i++) {
        CPPUNIT_ASSERT(roughlyEqual(correctSubMat[i], subMat[i]));
    }
}

void TestMatrix::testInverse() {
    float elems[16] = {1, 5, 9, 4, 
                       5, 2, 7, 8, 
                       9, 10, 1, 12, 
                       13, 20, 15, 4};
    const Matrix m3(elems);
    Matrix inv = m3.getInverse();
    Matrix prod = inv*m3;
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            if(row == col) {
                CPPUNIT_ASSERT(roughlyEqual(prod.getElem(row, col), 1.0));//check we've got the identity matrix
            } else {
                CPPUNIT_ASSERT(roughlyEqual(prod.getElem(row, col), 0.0));
            }
        }
    }
}

void TestMatrix::testTranslation() {
    TranslationMat mat(1, 2, 3);
    Point p2 = mat*(*p1);
    CPPUNIT_ASSERT(p2.roughlyEqual(Point(2, 4, 6)));
}

void TestMatrix::testScaling() {
    ScalingMat mat(1, 2, 3);
    Point p2 = mat*(*p1);
    Vec v2 = mat*(*v1);

    CPPUNIT_ASSERT(p2.roughlyEqual(Point(1, 4, 9)));
    CPPUNIT_ASSERT(v2.roughlyEqual(Vec(2, 6, 12)));
}

void TestMatrix::testRotation() {
    XRotation xRot(1);
    YRotation yRot(2);
    ZRotation zRot(3);

    Point p2 = xRot*(*p1);
    Vec v2 = xRot*(*v1);

    CPPUNIT_ASSERT(p2.roughlyEqual(Point(1, -1.4438, 3.303849)));
    CPPUNIT_ASSERT(v2.roughlyEqual(Vec(2, -1.74498, 4.685622)));

    Point p3 = yRot*(*p1);

    CPPUNIT_ASSERT(p3.roughlyEqual(Point(2.3117455, 2, -2.1577379)));

    Point p4 = zRot*(*p1);

    CPPUNIT_ASSERT(p4.roughlyEqual(Point(-1.272233, -1.838865, 3)));
}

void TestMatrix::testShear() {
    ShearMat shear1(1.0, 0, 0, 0, 0, 0);
    ShearMat shear2(0, 1.0, 0, 0, 0, 0);
    ShearMat shear3(0, 0, 1.0, 0, 0, 0);
    ShearMat shear4(0, 0, 0, 1.0, 0, 0);
    ShearMat shear5(0, 0, 0, 0, 1.0, 0);
    ShearMat shear6(0, 0, 0, 0, 0, 1.0);

    Point p2 = shear1*(*p1);
    Point p3 = shear2*(*p1);
    Point p4 = shear3*(*p1);
    Point p5 = shear4*(*p1);
    Point p6 = shear5*(*p1);
    Point p7 = shear6*(*p1);

    CPPUNIT_ASSERT(p2.roughlyEqual(Point(3, 2, 3)));

    CPPUNIT_ASSERT(p3.roughlyEqual(Point(4, 2, 3)));

    CPPUNIT_ASSERT(p4.roughlyEqual(Point(1, 3, 3)));

    CPPUNIT_ASSERT(p5.roughlyEqual(Point(1, 5, 3)));

    CPPUNIT_ASSERT(p6.roughlyEqual(Point(1, 2, 4)));

    CPPUNIT_ASSERT(p7.roughlyEqual(Point(1, 2, 5)));
}

CppUnit::Test* TestMatrix::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Matrix Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test identity", &TestMatrix::testIdentity));
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test translation mat", &TestMatrix::testTranslation));
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test scaling mat", &TestMatrix::testScaling));
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test rotation mat", &TestMatrix::testRotation));
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test shear mat", &TestMatrix::testShear));

    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test Matrix Matrix Multiply", &TestMatrix::testMatMatMultiply));
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test Transpose", &TestMatrix::testTranspose));

    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test 3D Determinant", &TestMatrix::testDet3D));
    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test Sub Matrix", &TestMatrix::testSubMat4D));

    testSuite->addTest(new CppUnit::TestCaller<TestMatrix>("Test Transpose", &TestMatrix::testInverse));

    return testSuite;
}