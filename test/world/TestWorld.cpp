#include "TestWorld.h"

void TestWorld::setUp() {}

void TestWorld::tearDown() {}

void TestWorld::testWorld() {
    World w(PointLight(Point(0, 0, 0), Colour(1, 1, 1)));
    CPPUNIT_ASSERT(w.getPointLight().getOrigin().roughlyEqual(Point(0, 0, 0)));
    CPPUNIT_ASSERT(w.getPointLight().getIntensity().roughlyEqual(Colour(1, 1, 1)));
}

void TestWorld::testAddObject() {
    World w(PointLight(Point(0, 0, 0), Colour(1, 1, 1)));
    w.addMaterial(Material(0.1, 0.2, 0.3, 100, Colour(0.5, 0.6, 0.7)));
    w.addMaterial(Material(0.15, 0.25, 0.35, 100, Colour(0.55, 0.65, 0.75)));
    CPPUNIT_ASSERT(w.getNumMaterials() == 2);

    w.addObject(TSphere(), 1);

    bool exception = false;

    try {
        w.addObject(TSphere(), 2);
    } catch(IndexOutOfBounds e) {
        exception = true;
    }

    const Object* obj1Ptr = w.getObject(0);
    CPPUNIT_ASSERT(roughlyEqual(obj1Ptr->getMaterial()->getAmbient(), 0.15));
    CPPUNIT_ASSERT(roughlyEqual(obj1Ptr->getMaterial()->getDiffuse(), 0.25));
    CPPUNIT_ASSERT(roughlyEqual(obj1Ptr->getMaterial()->getSpecular(), 0.35));
    CPPUNIT_ASSERT(obj1Ptr->getMaterial()->getColour().roughlyEqual(Colour(0.55, 0.65, 0.75)));
}

void TestWorld::testAddMaterial() {
    World w(PointLight(Point(0, 0, 0), Colour(1, 1, 1)));
    w.addMaterial(Material(0.1, 0.2, 0.3, 100, Colour(0.5, 0.6, 0.7)));
    w.addMaterial(Material(0.15, 0.25, 0.35, 100, Colour(0.55, 0.65, 0.75)));
    CPPUNIT_ASSERT(w.getNumMaterials() == 2);
}

void TestWorld::testIntersection() {
    World w(PointLight(Point(0, 0, 0), Colour(1, 1, 1)));
    w.addMaterial(Material(0.1, 0.2, 0.3, 100, Colour(0.5, 0.6, 0.7)));
    w.addMaterial(Material(0.15, 0.25, 0.35, 100, Colour(0.55, 0.65, 0.75)));
    w.addObject(TSphere(ScalingMat(2, 2, 2)), 1);
    w.addObject(TSphere(), 0);
    IntersectionSpec intSpec1 = w.getIntersection(Ray(Point(0.5, 0, 0), Vec(3, 0, 0)));
    IntersectionSpec intSpec2 = w.getIntersection(Ray(Point(0, 3, 0), Vec(0, -2, 0)));

    CPPUNIT_ASSERT(intSpec1.norm.roughlyEqual(Vec(-1, 0, 0)));
    CPPUNIT_ASSERT(intSpec1.point.roughlyEqual(Point(1, 0, 0)));
    CPPUNIT_ASSERT(intSpec1.obj1 == w.getObject(1));
    CPPUNIT_ASSERT(intSpec1.obj2 == w.getObject(0));
    CPPUNIT_ASSERT(intSpec1.lightVec.roughlyEqual(Vec(-1, 0, 0)));
    
    CPPUNIT_ASSERT(intSpec2.norm.roughlyEqual(Vec(0, 1, 0)));
    CPPUNIT_ASSERT(intSpec2.point.roughlyEqual(Point(0, 2, 0)));
    CPPUNIT_ASSERT(intSpec2.obj1 == NULL);
    CPPUNIT_ASSERT(intSpec2.obj2 == w.getObject(0));
    CPPUNIT_ASSERT(intSpec2.lightVec.roughlyEqual(Vec(0, -1, 0)));
}

CppUnit::Test* TestWorld::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("World Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test world", &TestWorld::testWorld));
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test adding objects", &TestWorld::testAddObject));
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test adding materials", &TestWorld::testAddMaterial));
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test intersection", &TestWorld::testIntersection));

    return testSuite;
}