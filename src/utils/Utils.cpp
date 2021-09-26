#include "Utils.h"

bool roughlyEqual(float a, float b) {
    float delta = a - b;
    return delta < 0.00001 && delta > -0.00001;
}