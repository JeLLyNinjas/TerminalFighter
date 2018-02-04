#pragma once

#include <map>

enum class RenderType {
    Blended,
    Shaded,
    Solid,
}

class JN_TTF {
    public: 
        JN_TTF();
        ~JN_TTF();
        int open_font(std::string path, int font_size);
        SDL_Surface* TTF_RenderText(RenderType type, std::string font_type, SDL_Color color);

    private:
        sdt::map<std::string, TTF_Font*> font_map_;
};
