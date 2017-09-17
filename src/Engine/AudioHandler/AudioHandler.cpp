#include <glog/logging.h>

#include <SDL.h>
#include <stdio.h>
#include <string>

#include "AudioHandler.h"


AudioHandler::AudioHandler() {

}
AudioHandler::~AudioHandler() {
    //TODO make sure this thing cleans things up
    //for (std::map<std::string, Mix_Chunk*>::iterator it = sound_effects_.begin(); it != sound_effects_.end(); ++it) {
    //Mix_FreeChunk(it->second);
    //}
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
}
void AudioHandler::play_chunk(Mix_Chunk* chunk) {
    Mix_PlayChannel(-1, chunk, 0);
}
