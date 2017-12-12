#include <math.h>
#include <stdio.h>

#include "Util/Util.h"

namespace {
    const double PI = 3.14159265358979323846264338327950288;

    const double MAX_GAME_WIDTH = 0.5625;
    const double MIN_GAME_WIDTH = -MAX_GAME_WIDTH;
    const double MAX_GAME_HEIGHT = 1.0;
    const double MIN_GAME_HEIGHT = -MAX_GAME_HEIGHT;
}

float Util::inverse_sqrt(float magnitude) {
    float magnitude_half = 0.5 * magnitude;
    int i = *(int*)&magnitude;
    i = 0x5f3759df - (i >> 1);
    magnitude = *(float*)&i;
    return magnitude * (1.5f - magnitude_half * magnitude * magnitude);
}

// Angle counterclockwise from vertical in degrees
double Util::angle(double from_x, double from_y, double to_x, double to_y) {
    double delta_x = to_x - from_x;
    double delta_y = to_y - from_y;

    double theta_radians = atan2(delta_y, delta_x);

    // Convert to degrees
    // Add by 90 to set angle from vertical (12 o'clock)
    // As opposed to the normal angle in standard trig (3 o'clock)
    double normal_angle = (theta_radians * 180 / PI) + 90;
    return normal_angle;
}

double Util::max_game_width() {
    return MAX_GAME_WIDTH;
}

double Util::min_game_width() {
    return MIN_GAME_WIDTH;
}

double Util::max_game_height() {
    return MAX_GAME_HEIGHT;
}

double Util::min_game_height() {
    return MIN_GAME_HEIGHT;
}


