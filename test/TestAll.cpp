#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "test/utils/TestUtils.h"
#include "test/geometry/TestTuple.h"
#include "test/geometry/TestMatrix.h"

int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TestUtils::suite());
    runner.addTest(TestTuples::suite());
    runner.addTest(TestMatrix::suite());
    runner.run();
    return 0;
}