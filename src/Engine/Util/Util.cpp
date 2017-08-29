#include "Util/Util.h"

float util::inverse_sqrt(float magnitude) {
    float magnitude_half = 0.5 * magnitude;
    int i = *(int*)&magnitude;
    i = 0x5f3759df - (i >> 1);
    magnitude = *(float*)&i;
    return magnitude * (1.5f - magnitude_half * magnitude * magnitude);
}
