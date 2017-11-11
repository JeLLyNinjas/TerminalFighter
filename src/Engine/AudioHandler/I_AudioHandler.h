#pragma once

#include <string>
#include <memory>

#include <SDL2/SDL_mixer.h>

enum class Channel : int {
    ANY_CHANNEL = -1,
    CHANNEL_1 = 1
};

class I_AudioHandler {
public:
    virtual ~I_AudioHandler() {}
    virtual void init() = 0;
    virtual void play_music(std::string path) const = 0;
    virtual void play_chunk(std::string path) const = 0;
};
