#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "test/utils/TestUtils.h"
#include "test/basicConstructs/TestTuple.h"
#include "test/basicConstructs/TestMatrix.h"
#include "test/basicConstructs/TestColour.h"
#include "test/basicConstructs/TestRay.h"
#include "test/world/object/material/TestMaterial.h"
#include "test/world/object/shape/TestTSphere.h"
#include "test/world/object/TestIntersection.h"
#include "test/world/object/TestObject.h"
#include "test/world/light/TestPointLight.h"
#include "test/world/TestWorld.h"
#include "test/camera/TestCanvas.h"

int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TestUtils::suite());
    runner.addTest(TestTuples::suite());
    runner.addTest(TestMatrix::suite());
    runner.addTest(TestColour::suite());
    runner.addTest(TestRay::suite());
    runner.addTest(TestMaterial::suite());
    runner.addTest(TestTSphere::suite());
    runner.addTest(TestIntersection::suite());
    runner.addTest(TestObject::suite());
    runner.addTest(TestPointLight::suite());
    runner.addTest(TestWorld::suite());
    runner.addTest(TestCanvas::suite());
    runner.run();
    return 0;
}