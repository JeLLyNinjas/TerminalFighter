#pragma once

class Util {
public:
    static float inverse_sqrt(float x);
    static double angle(double from_x, double from_y, double to_x, double to_y);
    static double max_game_width();
    static double min_game_width();
    static double max_game_height();
    static double min_game_height();
};
