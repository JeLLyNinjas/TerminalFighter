#pragma once

#include <map>

#include "I_AudioHandler.h"


class AudioHandler : public I_AudioHandler {
public:
    ~AudioHandler();
    AudioHandler();
    void init();
    //void play_music(std::string path) const;
    void play_chunk(std::string path) const;

private:

    std::map <std::string, std::unique_ptr<Mix_Chunk*>> sound_effects_;
};
