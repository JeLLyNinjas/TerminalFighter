#pragma once

class I_AudioHandler {
public:
    virtual ~I_AudioHandler() {}
    virtual void init() = 0;
    virtual Mix_Music* load_music(std::string path) = 0;
    virtual Mix_Chunk* load_chunk(std::string path) = 0;
};
