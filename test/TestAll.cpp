#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "test/utils/TestUtils.h"
#include "test/geometry/TestTuple.h"

int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TestUtils::suite());
    runner.addTest(TestTuples::suite());
    runner.run();
    return 0;
}