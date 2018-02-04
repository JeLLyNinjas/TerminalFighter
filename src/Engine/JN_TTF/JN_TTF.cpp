#include "JN_TTF.h"

JN_TTF::JN_TTF() 
{}

JN_TTF::~JN_TTF() {
    //Delete the TTF_Font*'s within the font_map_
    for (auto it = font_map_.begin(); it != font_map_.end(); ++it) {
        delete it->second;
    }
}

int JN_TTF::open_font(std::string path, int font_size) {
    TTF_Font *temp = NULL;
    temp = TTF_OpenFont(path, font_size);
    if (temp == NULL) {
        LOG(ERROR) << "Failed to load " << path;
        return -1;
    }
    font_map_[path] = temp;
    return 0;
}

SDL_Surface *JN_TTF::TTF_RenderText(RenderType type, std::string font_type, SDL_Color color) {
    //TTF_OpenFont(font_map_[font_type.c_str()] 
}
