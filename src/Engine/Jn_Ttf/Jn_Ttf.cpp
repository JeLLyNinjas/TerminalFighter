#include "Jn_Ttf.h"

Jn_Ttf::Jn_Ttf() 
    :default_font_size_(48)
{}

Jn_Ttf::~Jn_Ttf() {
    //Delete the TTF_Font*'s within the font_map_
    for (auto it = font_map_.begin(); it != font_map_.end(); ++it) {
        TTF_CloseFont(it->second); //using the included TTF_CloseFont function 
    }
}

int Jn_Ttf::Jn_Ttf_RenderText(std::string text, 
                RenderType type, 
                std::string font_path, 
                SDL_Color color,
                int font_render_size,
                double font_output_size,
                SDL_Surface *&surface_ref,
                SDL_Rect &sdl_rect_ref,
                JN_Rect &jn_rect_ref) {

    auto iterator = font_map_.find(font_path);
    if (iterator == font_map_.end()) {
        LOG(INFO) << "Could not find font " << font_path << ". Loading Font Now...";
        //.find could not find font_path
        if (open_font(font_path, default_font_size_) != 0) {
            LOG(ERROR) << "Unable to render text due to unknown font" << font_path;
            return -1;
        }
        iterator = font_map_.find(font_path);
    } 
    
    SDL_Surface *surface_text = RenderText(text, type, iterator->second, color, font_render_size);
    if (surface_text == NULL) {
        LOG(ERROR) << "Unable to Render Text:" << TTF_GetError();
        return -1;
    }
    surface_ref = surface_text;

    sdl_rect_ref.x = 0;
    sdl_rect_ref.y = 0;
    sdl_rect_ref.w = surface_ref->w;
    sdl_rect_ref.h = surface_ref->h;

    // We will use font_output_size as the height, and then
    // using the ratio, calculate the corresponding width
    int ratio = sdl_rect_ref.w / sdl_rect_ref.h;

    jn_rect_ref.x = 0;
    jn_rect_ref.y = 0;
    jn_rect_ref.w = font_output_size* ratio;
    jn_rect_ref.h = font_output_size;

    return 0;
}

int Jn_Ttf::open_font(std::string path, int font_size) {
    if (font_map_.find(path) != font_map_.end()) {
        //Font already exists, returning 0 for no error. 
        DLOG(INFO) << "Font " << path << " already exists";
        return 0;
    }
    
    TTF_Font *temp = NULL;
    temp = TTF_OpenFont(path.c_str(), font_size);
    if (temp == NULL) {
        LOG(ERROR) << "Failed to load " << path;
        return -1;
    }
    font_map_[path] = temp;
    return 0;
}


SDL_Surface *Jn_Ttf::RenderText(std::string text,
        RenderType type, 
        TTF_Font* font, 
        SDL_Color color, 
        int font_render_size) {

    SDL_Surface *text_surface;
    switch(type) {
        case RenderType::Blended: {
            text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
        }
        case RenderType::Solid: {
            text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
        }
    }
    return text_surface;
}
