#include <glog/logging.h>

#include "GraphicsHandler.h"

namespace {
    const std::vector<GraphicPriority> DRAW_ORDER = {
        GraphicPriority::BACKGROUND,
        GraphicPriority::BACK,
        GraphicPriority::MIDDLE,
        GraphicPriority::FRONT,
        GraphicPriority::UI,
        GraphicPriority::OVERLAY
    };
}

GraphicsHandler::GraphicsHandler(SDL_Renderer& renderer)
    : renderer_(renderer)
    , draw_queue_( {
    {GraphicPriority::OVERLAY, std::vector<DrawRequest>() },
    {GraphicPriority::UI, std::vector<DrawRequest>() },
    {GraphicPriority::FRONT, std::vector<DrawRequest>() },
    {GraphicPriority::MIDDLE, std::vector<DrawRequest>() },
    {GraphicPriority::BACK, std::vector<DrawRequest>() },
    {GraphicPriority::BACKGROUND, std::vector<DrawRequest>() }
}) {
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           SDL_Rect texture_rect,
                           GraphicPriority priority,
                           bool is_flyweight,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {
    draw_queue_.at(priority).push_back(DrawRequest(texture, texture_rect, is_flyweight, angle_clockwise, rotation_point));
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           int x_pos,
                           int y_pos,
                           GraphicPriority priority,
                           bool is_flyweight,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {
    SDL_Rect texture_rect;
    SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
    texture_rect.x = x_pos;
    texture_rect.y = y_pos;
    this->draw(texture, texture_rect, priority, is_flyweight, angle_clockwise, rotation_point);
}

void GraphicsHandler::draw(SDL_Surface* surface,
                           int x_pos,
                           int y_pos,
                           GraphicPriority priority,
                           bool is_flyweight,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer_, surface);
    this->draw(texture, x_pos, y_pos, priority, is_flyweight, angle_clockwise, rotation_point);
}


void GraphicsHandler::update_screen() {
    for (auto priority : DRAW_ORDER) {
        for (auto const& draw_request : draw_queue_[priority]) {
            SDL_RenderCopyEx(&renderer_, draw_request.texture(), NULL, &draw_request.texture_rect(),
                             draw_request.angle(), draw_request.rotation_point(), SDL_FLIP_NONE);

            if (!draw_request.cleanup()) {
                SDL_DestroyTexture(draw_request.texture());
            }
        }

        draw_queue_.at(priority) = std::vector<DrawRequest>();
    }

    SDL_RenderPresent(&renderer_);
    SDL_SetRenderDrawColor(&renderer_, 0x00, 0x00, 0x00, 0x00 ); //clears the screen to the color black
    SDL_RenderClear(&renderer_);
}

//TODO make this function load from a list of objects defined in a text file (.INI file maybe?) depending on each game state enum.
//Right now, this function should just load all of our assets. Maybe later when we need to conserve more space, load only things we need
//defined by .INI
void GraphicsHandler::init() {
    game_graphics_["assets/projectiles/missile.png"] = internal_load_image("assets/projectiles/missile.png");
    game_graphics_["assets/ships/BasicEnemy.png"] = internal_load_image("assets/ships/BasicEnemy.png");
    game_graphics_["assets/ships/Arman.png"] = internal_load_image("assets/ships/Arman.png");
    game_graphics_["assets/terminal/futureui1.png"] = internal_load_image("assets/terminal/futureui1.png");
}

SDL_Texture* GraphicsHandler::internal_load_image(std::string path) {
    SDL_Surface* image_surface = IMG_Load(path.c_str());
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(&renderer_, image_surface);
    SDL_FreeSurface(image_surface);
    return image_texture;
}

SDL_Texture* GraphicsHandler::load_image(std::string path) {
    if (game_graphics_.find(path) == game_graphics_.end() ) {
        LOG(FATAL) << "Fatal error, could not find the sprite " << path.c_str() << "! Exiting...";
    }

    return game_graphics_.find(path)->second;
}

