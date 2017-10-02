#include <glog/logging.h>

#include <SDL.h>
#include <stdio.h>
#include <string>

#include "AudioHandler.h"


AudioHandler::AudioHandler() {

}
AudioHandler::~AudioHandler() {
}
void AudioHandler::init() {
    //TODO only load really important things that need early access Like... Splash screen music or w/e
}
Mix_Music* AudioHandler:: load_music(std::string path) {
    Mix_Music* ret = Mix_LoadMUS(path.c_str());

    if ( ret == NULL ) {
        LOG(FATAL) << "Fatal error, could not load music: " << path.c_str() <<
                   "Error: " << Mix_GetError() << " Exiting...";
    }

    return ret;
}
Mix_Chunk* AudioHandler:: load_chunk(std::string path) {
    Mix_Chunk* ret = Mix_LoadWAV(path.c_str());

    if ( ret == NULL ) {
        LOG(FATAL) << "Fatal error, could not load chunk: " << path.c_str() <<
                   "Error: " << Mix_GetError() << " Exiting...";
    }

    sound_effects_[path.c_str()] = ret;

    return ret;
}
void AudioHandler::play_music(Mix_Music* music) {
    //TODO
    //// Mix_Music *music; // I assume this has been loaded already
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
        // well, there's no music, but most games don't break without music...
    }
}
void AudioHandler::play_chunk(Mix_Chunk* chunk) {
    if (Mix_PlayChannel(-1, chunk, 0) == -1) {
        LOG(ERROR) << "Mix_PlayChannel: " << Mix_GetError();
        printf("What\n");
    }
}
