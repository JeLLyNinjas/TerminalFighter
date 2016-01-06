#include "graphics_handler.h"

GraphicsHandler::GraphicsHandler(SDL_Renderer *renderer) {
    renderer_ = renderer;
}

void GraphicsHandler::draw(SDL_Texture *texture, SDL_Rect texture_rect) {
    SDL_RenderCopy(renderer_, texture, NULL, &texture_rect);
}

void GraphicsHandler::draw(SDL_Texture *texture, int x_pos, int y_pos) {
    SDL_Rect texture_rect;
    SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
    texture_rect.x = x_pos;
    texture_rect.y = y_pos;
    SDL_RenderCopy(renderer_, texture, NULL, &texture_rect);
}

void GraphicsHandler::update_screen() {
    SDL_RenderPresent(renderer_);
    SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0x00 ); //clears the screen to the color black
    SDL_RenderClear(renderer_);
}

//TODO make this function load from a list of objects defined in a text file (.INI file maybe?) depending on each game state enum.
//Right now, this function should just load all of our assets. Maybe later when we need to conserve more space, load only things we need
//defined by .INI
void GraphicsHandler::init() {
    game_graphics_["assets/projectiles/missile.png"] = internal_load_image("assets/projectiles/missile.png");
}

SDL_Texture *GraphicsHandler::internal_load_image(std::string path) {
    SDL_Surface *image_surface = IMG_Load(path.c_str());
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer_, image_surface);
    SDL_FreeSurface(image_surface);
    return image_texture;
}

SDL_Texture *GraphicsHandler::load_image(std::string path) {
    if (game_graphics_.find(path) == game_graphics_.end() ) {
        printf("Fatal error, could not find the sprite %s! Exiting program\n", path.c_str());
    } else {
        return game_graphics_.find(path)->second;
    }
}

