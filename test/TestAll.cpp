#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "test/utils/TestUtils.h"
#include "test/geometry/TestTuple.h"
#include "test/geometry/TestMatrix.h"
#include "test/utils/TestColour.h"
#include "test/geometry/TestRay.h"

int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TestUtils::suite());
    runner.addTest(TestTuples::suite());
    runner.addTest(TestMatrix::suite());
    runner.addTest(TestColour::suite());
    runner.addTest(TestRay::suite());
    runner.run();
    return 0;
}