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
