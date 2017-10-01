#include <glog/logging.h>

#include "Delay.h"

Delay::Delay(bool debug_mode, std::string fps_font_path) {
    started_ = false;
    debug_mode_ = debug_mode;
    default_delay_font_ = TTF_OpenFont(fps_font_path.c_str(), 84);

    if (default_delay_font_ == NULL) {
        LOG(ERROR) << "Failed to load default_delay_font_ " << fps_font_path;
    } else {
        LOG(INFO) << "Successfully loaded default_delay_font_ " << fps_font_path;
    }

    lowest_fps = 1000000; //arbitrary large number
}

Delay::~Delay() {
    if (default_delay_font_ != NULL) {
        TTF_CloseFont(default_delay_font_);
    }
}

void Delay::delay_with_fps(double fps) {
    if (started_ == false) {
        started_ = true;
        start_timer();
    } else {
        stop_timer();
        double time_to_achieve_fps = (1 / fps) * 1000000;
        time_duration_ = duration_cast<microseconds>(time_end - time_start);
        time_to_achieve_fps = time_to_achieve_fps - time_duration_.count();

        if (time_to_achieve_fps > 0) {
            usleep(time_to_achieve_fps);
        }

        if (debug_mode_) {
            LOG(INFO) << "Time between loops: " << (int)time_duration_.count();
            LOG(INFO) << "Time needed between loops: " << time_to_achieve_fps;
        }

        start_timer();
    }
}

void Delay::start_timer() {
    time_start = high_resolution_clock::now();
}

void Delay::stop_timer() {
    time_end = high_resolution_clock::now();
}

SDL_Surface* Delay::grab_frame_rate() {
    SDL_Color frame_rate_color = {255, 255, 255};

    if (lowest_fps > 1 / ((double)time_duration_.count() / 1000000) && 10 < 1 / ((double)time_duration_.count() / 1000000)) {
        lowest_fps = 1 / ((double)time_duration_.count() / 1000000);
        LOG(INFO) << "lowest fps is now " << lowest_fps;
    }

    return TTF_RenderText_Blended(default_delay_font_, std::to_string(1 / ((double)time_duration_.count() / 1000000)).c_str(), frame_rate_color);
}
