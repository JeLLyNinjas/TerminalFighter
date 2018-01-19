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

GraphicsHandler::GraphicsHandler(
    SDL_Renderer& renderer,
    std::vector<std::string> graphic_paths,
    int screen_width,
    int screen_height)
    : renderer_(renderer)
    , draw_queue_( {
    {GraphicPriority::OVERLAY, std::vector<DrawRequest>() },
    {GraphicPriority::UI, std::vector<DrawRequest>() },
    {GraphicPriority::FRONT, std::vector<DrawRequest>() },
    {GraphicPriority::MIDDLE, std::vector<DrawRequest>() },
    {GraphicPriority::BACK, std::vector<DrawRequest>() },
    {GraphicPriority::BACKGROUND, std::vector<DrawRequest>() }
}) {
    init(graphic_paths);
}


JN_Rect create_jn_rect(double x, 
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

void GraphicsHandler::draw(SDL_Texture* texture,
                           JN_Rect src_rect,
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

//TODO make this 1-1gamestate
void GraphicsHandler::update_screen() {
    for (auto priority : DRAW_ORDER) {
        for (auto const& draw_request : draw_queue_[priority]) {
            SDL_RenderCopyEx(&renderer_,
                    draw_request.texture(),
                    create_sdl_rect(draw_request.src_rect()),
                    create_sdl_rect(draw_request.dest_rect()),
                    draw_request.angle(),
                    draw_request.rotation_point(),
                    SDL_FLIP_NONE);

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


const SDL_Rect* GraphicsHandler::create_sdl_rect(const JN_Rect& rect) {
    // We need to convert x and y from -1 to 1 into 0 and something like 1920
    // Some Notes. We are assuming people can run with any resolution
    // as long as it is using the 16:9 ratio.
    // 1024x576, 1152x648, 1280x720, 1366x768, 1600x900, 1920x1080, 2560x1440 3840x2160.

    // The algorithm is as follows
    // for example, say we have 1920 as our screen_width_
    // we will need a variable: half_screen_width = 960
    // we will multiply our x (which is a range of -1 to 1) with the half_screen_width.
    // so example, if we had -1, it becomes -960, and if we had 1, it would becom 960.
    // We then add them to half_screen_width (960) and we get a range of numbers between 0 and 1920.

    SDL_Rect *sdl_rect;
    int half_screen_width = screen_width_/2;    
    sdl_rect->x = (rect.x * half_screen_width) + half_screen_width;
    sdl_rect->w = (rect.w * half_screen_width) + half_screen_width;

    int half_screen_height = screen_height_/2;    
    sdl_rect->y = (rect.x * half_screen_height) + half_screen_height;
    sdl_rect->h = (rect.w * half_screen_height) + half_screen_height;
    // TODO haven't really confirmed if this works. Math needs to be checked
    // Also, this is probably pretty performance sensitive as it will be called
    // for every object that needs to be drawn for every loop. Maybe find some hack to calculate
    // this stuff faster? -Ex. Width and Height probably don't need to be re-calculated everytime
    

    // TODO!!! Sleeping now. This function cannot happen here. As it is right now, this will 
    // be a memory leak with *sdl_rect never being freed.
    //
    // However, this function also can't be `const SDL_Rect&` return just like 
    // the DrawRequest class because we'd be turning a static SDL_Rect sdl_rect local to this function
    // and passing it as a reference out of this function.. which would then be destroyed before it
    // enters the SDL_RenderCopyEx. We need to probably add a `SDL_Rect` into DrawRequest.
    return sdl_rect;
}





















