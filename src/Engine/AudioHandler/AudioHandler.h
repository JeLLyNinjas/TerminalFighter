#pragma once

#include <map>

#include "I_AudioHandler.h"

class AudioHandler : public I_AudioHandler {
public:
    ~AudioHandler();
    AudioHandler();
    void init();
    Mix_Music* load_music(std::string path);
    Mix_Chunk* load_chunk(std::string path);
    void play_music(Mix_Music* music);
    void play_chunk(Mix_Chunk* chunk);

private:
    SDL_Texture* internal_load_image(std::string path);

    std::map <std::string, Mix_Chunk*> sound_effects_;
};
