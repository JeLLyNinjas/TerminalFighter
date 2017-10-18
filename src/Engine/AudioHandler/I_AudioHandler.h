#pragma once

#include <string>

#include <SDL2/SDL_mixer.h>

class I_AudioHandler {
public:
    virtual ~I_AudioHandler() {}
    virtual void init() = 0;
    virtual Mix_Music* load_music(std::string path) = 0;
    virtual Mix_Chunk* load_chunk(std::string path) = 0;
    virtual void play_music(Mix_Music* music) const = 0;
    virtual void play_chunk(Mix_Chunk* chunk) const = 0;
};
