#include <string>
#include <stdio.h>

#include <glog/logging.h>
#include <SDL.h>

#include "AudioHandler.h"


AudioHandler::AudioHandler() {

}
AudioHandler::~AudioHandler() {
}
void AudioHandler::init() {
    //TODO only load really important things that need early access Like... Splash screen music or w/e
}

void AudioHandler::play_music(std::string path) const {
    LOG(FATAL) << "Function should not be used yet";
}

void AudioHandler::play_chunk(std::string path) const {
    Mix_Chunk* temp = NULL;
    auto iterator = sound_effects_.find(path);

    //iterator will == end() if .find() cannot find path
    //so we need to load the sound
    if ( iterator == sound_effects_.end()) {
        temp = Mix_LoadWAV(path.c_str());

        if ( temp == NULL ) {
            LOG(FATAL) << "Fatal error, could not load chunk: " << path.c_str()
                       << "Error: " << Mix_GetError() << " Exiting...";
        }

        std::unique_ptr<Mix_Chunk *> chunk = std::make_unique<Mix_Chunk *>(temp);
    } else {
        temp = *iterator->second.get();
    }

    if (Mix_PlayChannel(static_cast<int>(Channel::ANY_CHANNEL), temp, 0) == -1) {
        LOG(ERROR) << "Mix_PlayChannel: " << Mix_GetError();
    }
}
