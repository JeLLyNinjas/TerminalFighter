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
Mix_Music* AudioHandler:: load_music(std::string path) {
    LOG(FATAL) << "Function should not be used yet";
    //Mix_Music* ret = Mix_LoadMUS(path.c_str());

    //if ( ret == NULL ) {
    //LOG(FATAL) << "Fatal error, could not load music: " << path.c_str() <<
    //"Error: " << Mix_GetError() << " Exiting...";
    //}

    //return ret;
}
Mix_Chunk* AudioHandler:: load_chunk(std::string path) {
    Mix_Chunk* ret = NULL;
    auto iterator = sound_effects_.find(path);

    if ( iterator != sound_effects_.end()) {
        ret = iterator->second;
    } else {
        ret = Mix_LoadWAV(path.c_str());

        if ( ret == NULL ) {
            LOG(FATAL) << "Fatal error, could not load chunk: " << path.c_str() <<
                       "Error: " << Mix_GetError() << " Exiting...";
        }

        sound_effects_[path.c_str()] = ret;
    }

    return ret;

}
void AudioHandler::play_music(Mix_Music* music) {
    LOG(FATAL) << "Function should not be used yet";
    //TODO just keeping code here
    //if (Mix_PlayMusic(music, -1) == -1) {
    //printf("Mix_PlayMusic: %s\n", Mix_GetError());
    //}
}
void AudioHandler::play_chunk(Mix_Chunk* chunk) {
    if (Mix_PlayChannel(-1, chunk, 0) == -1) {
        LOG(ERROR) << "Mix_PlayChannel: " << Mix_GetError();
    }
}
