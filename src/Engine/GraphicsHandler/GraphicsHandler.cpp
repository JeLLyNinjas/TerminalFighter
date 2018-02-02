#include <glog/logging.h>

#include "GraphicsHandler.h"
#include <stdio.h>

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

GraphicsHandler::~GraphicsHandler() {

}

GraphicsHandler::GraphicsHandler(
    SDL_Renderer& renderer,
    std::vector<std::string> graphic_paths,
    int screen_width,
    int screen_height)
    : renderer_(renderer), 
    screen_width_(screen_width),
    screen_height_(screen_height),
    draw_queue_( {
    {GraphicPriority::OVERLAY, std::vector<DrawRequest>() },
    {GraphicPriority::UI, std::vector<DrawRequest>() },
    {GraphicPriority::FRONT, std::vector<DrawRequest>() },
    {GraphicPriority::MIDDLE, std::vector<DrawRequest>() },
    {GraphicPriority::BACK, std::vector<DrawRequest>() },
    {GraphicPriority::BACKGROUND, std::vector<DrawRequest>() }
}) {
    init(graphic_paths);
}


JN_Rect GraphicsHandler::create_jn_rect(double x, 
                        double y,
                        double w,
                        double h) {
    JN_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

SDL_Rect GraphicsHandler::create_sdl_rect(int x, 
                        int y,
                        int w,
                        int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           SDL_Rect src_rect,
                           JN_Rect dest_rect,
                           GraphicPriority priority,
                           bool cleanup,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {
    draw_queue_.at(priority).push_back(DrawRequest(texture,
                src_rect,
                dest_rect,
                cleanup,
                angle_clockwise,
                rotation_point));
}

//Cleanup refers to the surface when a SDL_Surface* is passed in
void GraphicsHandler::draw(SDL_Surface* surface,
                           SDL_Rect src_rect,
                           JN_Rect dest_rect,
                           GraphicPriority priority,
                           bool cleanup,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer_, surface);

    if (cleanup) {
        SDL_FreeSurface(surface);
    }

    //Setting cleanup to be true regardless of original argument. We created a texture here, and we will not
    //be keeping it. GraphicsHandler needs to clean it up for us in the future.
    this->draw(texture, src_rect, dest_rect, priority, true, angle_clockwise, rotation_point);
}

//TODO make this 1-1gamestate
void GraphicsHandler::update_screen() {
    for (auto priority : DRAW_ORDER) {
        for (auto & draw_request : draw_queue_[priority]) {
            SDL_RenderCopyEx(&renderer_,
                    draw_request.texture(),
                    &draw_request.src_rect(),
                    &draw_request.dest_rect(screen_width_, screen_height_),
                    draw_request.angle(),
                    draw_request.rotation_point(),
                    SDL_FLIP_NONE);

            if (draw_request.cleanup()) {
                SDL_DestroyTexture(draw_request.texture());
            }
        }
        draw_queue_.at(priority) = std::vector<DrawRequest>();
    }
    SDL_RenderPresent(&renderer_);
    SDL_SetRenderDrawColor(&renderer_, 0x00, 0x00, 0x00, 0x00 ); //clears the screen to the color black
    SDL_RenderClear(&renderer_);
}

void GraphicsHandler::init(const std::vector<std::string>& graphic_paths) {
    for (auto path : graphic_paths) {
        game_graphics_[path] = internal_load_image(path);
    }
}

SDL_Texture* GraphicsHandler::internal_load_image(std::string path) {
    SDL_Surface* image_surface = IMG_Load(path.c_str());
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(&renderer_, image_surface);
    SDL_FreeSurface(image_surface);
    return image_texture;
}

SDL_Texture* GraphicsHandler::load_image(std::string path) {
    if (game_graphics_.find(path) == game_graphics_.end() ) {
        //TODO allow load_image to call internal_load_image
        LOG(FATAL) << "Fatal error, could not find the sprite " << path.c_str() << "! Exiting...";
    }
    return game_graphics_.find(path)->second;
}
