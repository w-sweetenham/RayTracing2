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

    w.addObject(TSphere(), basicMaterial(0.15, 0.25, 0.35, 100, Colour(0.55, 0.65, 0.75)));
    w.addObject(Cube(TranslationMat(3, 0, 0), 2), basicMaterial(0.1, 0.2, 0.3, 100, Colour(0.5, 0.6, 0.7)));

    bool exception = false;



    const Object* obj1Ptr = w.getObject(0);
    float ambient, diffuse, specular, shininess;
    obj1Ptr->material->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(0, 1, 0));
    CPPUNIT_ASSERT(roughlyEqual(ambient, 0.15));
    CPPUNIT_ASSERT(roughlyEqual(diffuse, 0.25));
    CPPUNIT_ASSERT(roughlyEqual(specular, 0.35));
    CPPUNIT_ASSERT(roughlyEqual(shininess, 100));
    CPPUNIT_ASSERT(obj1Ptr->getColour(Point(0, 1, 0)).roughlyEqual(Colour(0.55, 0.65, 0.75)));

    const Object* obj2Ptr = w.getObject(1);
    obj2Ptr->material->getSurfaceOpticParams(ambient, diffuse, specular, shininess, Point(0, 1, 0));
    CPPUNIT_ASSERT(roughlyEqual(ambient, 0.1));
    CPPUNIT_ASSERT(roughlyEqual(diffuse, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(specular, 0.3));
    CPPUNIT_ASSERT(roughlyEqual(shininess, 100));
    CPPUNIT_ASSERT(obj2Ptr->getColour(Point(1, 0, 0)).roughlyEqual(Colour(0.5, 0.6, 0.7)));
}

void TestWorld::testIntersection() {
    World w(PointLight(Point(0, 0, 0), Colour(1, 1, 1)));
    w.addObject(TSphere(ScalingMat(2, 2, 2)), basicMaterial(0.15, 0.25, 0.35, 100, Colour(0.55, 0.65, 0.75)));
    w.addObject(TSphere(), basicMaterial(0.1, 0.2, 0.3, 100, Colour(0.5, 0.6, 0.7)));
    IntersectionSpec intSpec1 = w.getIntersection(Ray(Point(0.5, 0, 0), Vec(3, 0, 0)));
    IntersectionSpec intSpec2 = w.getIntersection(Ray(Point(0, 3, 0), Vec(0, -2, 0)));
    IntersectionSpec intSpec3 = w.getIntersection(Ray(Point(0, 5, 0), Vec(1, 0, 0)));

    CPPUNIT_ASSERT(intSpec1.hit == true);
    CPPUNIT_ASSERT(intSpec1.norm.roughlyEqual(Vec(-1, 0, 0)));
    CPPUNIT_ASSERT(intSpec1.point.roughlyEqual(Point(1, 0, 0)));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.ambient, 0.1));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.diffuse, 0.2));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.specular, 0.3));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.shininess, 100));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.n1, 1));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.n2, 1));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.reflectivity, 0));
    CPPUNIT_ASSERT(roughlyEqual(intSpec1.transparency, 0));
    CPPUNIT_ASSERT(intSpec1.colour.roughlyEqual(Colour(0.5, 0.6, 0.7)));
    CPPUNIT_ASSERT(intSpec1.lightVec.roughlyEqual(Vec(-1, 0, 0)));
    CPPUNIT_ASSERT(intSpec1.lightIntensity.roughlyEqual(Colour(1, 1, 1)));
    CPPUNIT_ASSERT(intSpec1.isShadowed == false);
    
    CPPUNIT_ASSERT(intSpec2.hit == true);
    CPPUNIT_ASSERT(intSpec2.norm.roughlyEqual(Vec(0, 1, 0)));
    CPPUNIT_ASSERT(intSpec2.point.roughlyEqual(Point(0, 2, 0)));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.ambient, 0.15));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.diffuse, 0.25));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.specular, 0.35));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.shininess, 100));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.n1, 1));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.n2, 1));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.reflectivity, 0));
    CPPUNIT_ASSERT(roughlyEqual(intSpec2.transparency, 0));
    CPPUNIT_ASSERT(intSpec2.colour.roughlyEqual(Colour(0.55, 0.65, 0.75)));
    CPPUNIT_ASSERT(intSpec2.lightVec.roughlyEqual(Vec(0, -1, 0)));
    CPPUNIT_ASSERT(intSpec2.lightIntensity.roughlyEqual(Colour(1, 1, 1)));
    CPPUNIT_ASSERT(intSpec2.isShadowed == true);

    CPPUNIT_ASSERT(intSpec3.hit == false);
}

void TestWorld::testShadow() {
    World w(PointLight(Point(0, 2, 0), Colour(1, 1, 1)));
    w.addObject(TSphere(), basicMaterial(0.1, 0.8, 0.8, 100, Colour(1, 1, 1)));
    w.addObject(TSphere(TranslationMat(2, 2, 0)), basicMaterial(0.1, 0.8, 0.8, 100, Colour(1, 1, 1), 1.5, 0, 0.8));
    bool isShadowed = w.isShadowed(Point(0, 0, 0));
    CPPUNIT_ASSERT(isShadowed == true);
    isShadowed = w.isShadowed(Point(0, -2, 0));
    CPPUNIT_ASSERT(isShadowed == true);
    isShadowed = w.isShadowed(Point(2, 2, 0));//inside transparent sphere
    CPPUNIT_ASSERT(isShadowed == false);


    Ray r1(Point(0, 0, 0), Vec(0, 2, 0));
    Ray r2(Point(0, -2, 0), Vec(0, 2, 0));
    Ray r3(Point(0, 1.5, 0), Vec(0, -1, 0));

    IntersectionSpec i1 = w.getIntersection(r1);
    CPPUNIT_ASSERT(i1.isShadowed == true);
    IntersectionSpec i2 = w.getIntersection(r2);
    CPPUNIT_ASSERT(i2.isShadowed == true);
    IntersectionSpec i3 = w.getIntersection(r3);
    CPPUNIT_ASSERT(i3.isShadowed == false);
}

CppUnit::Test* TestWorld::suite()
{
    CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("World Tests");
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test world", &TestWorld::testWorld));
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test adding objects", &TestWorld::testAddObject));
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test intersection", &TestWorld::testIntersection));
    testSuite->addTest(new CppUnit::TestCaller<TestWorld>("Test shadow", &TestWorld::testShadow));

    return testSuite;
}