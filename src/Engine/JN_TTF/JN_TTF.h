#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <glog/logging.h>

enum class RenderType {
    Blended,
    Shaded,
    Solid,
};

class JN_TTF {
    public: 
        JN_TTF();
        ~JN_TTF();
        int open_font(std::string path, int font_size);
        SDL_Surface* JN_TTF_RenderText(std::string text, RenderType type, std::string font_path, SDL_Color color);

    private:
        const int default_font_size_;
        std::map<std::string, TTF_Font*> font_map_;
};
