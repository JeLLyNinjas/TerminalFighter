#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <glog/logging.h>

#include "JN_Rect/JN_Rect.h"

enum class RenderType {
    Blended,
    Solid,
};

class JN_TTF {
    public: 
        JN_TTF();
        ~JN_TTF();


        // font_render_size denotes what size should be passed into TTF_RenderText
        // font_output_size denotes the size in % of each character/letter in terms of the screen width
        int JN_TTF_RenderText(std::string text, 
                RenderType type, 
                std::string font_path, 
                SDL_Color color,
                int font_render_size,
                int font_output_size,
                SDL_Surface *&surface_ref,
                SDL_Rect &sdl_rect_ref,
                JN_Rect &jn_rect_ref);

    private:
        int open_font(std::string path, int font_size);
        
        SDL_Surface *RenderText(std::string text,
                RenderType type, 
                TTF_Font* font, 
                SDL_Color color, 
                int font_render_size); 

        const int default_font_size_;
        std::map<std::string, TTF_Font*> font_map_;
};
