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
    void play_music(Mix_Music* music) const;
    void play_chunk(Mix_Chunk* chunk) const;

private:
    std::map <std::string, Mix_Chunk*> sound_effects_;
};
