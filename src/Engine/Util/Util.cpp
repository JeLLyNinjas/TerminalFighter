#include "Util/Util.h"
#include <math.h>

#define PI 3.14159265

float util::inverse_sqrt(float magnitude) {
    float magnitude_half = 0.5 * magnitude;
    int i = *(int*)&magnitude;
    i = 0x5f3759df - (i >> 1);
    magnitude = *(float*)&i;
    return magnitude * (1.5f - magnitude_half * magnitude * magnitude);
}

double angle_from_vertical_vector_to(double from_x, double from_y, double to_x, double to_y) {
    double delta_x = to_x - from_x;
    double delta_y = from_y - to_y;

    double theta_radians = atan2(delta_y, delta_x);
    return theta_radians * 180 / PI;
}
