#include <glog/logging.h>

#include "Util/Util.h"

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
    std::vector<std::string> graphic_paths)
    : renderer_(renderer)
    , draw_queue_( {
    {GraphicPriority::OVERLAY, std::vector<DrawRequest>() },
    {GraphicPriority::UI, std::vector<DrawRequest>() },
    {GraphicPriority::FRONT, std::vector<DrawRequest>() },
    {GraphicPriority::MIDDLE, std::vector<DrawRequest>() },
    {GraphicPriority::BACK, std::vector<DrawRequest>() },
    {GraphicPriority::BACKGROUND, std::vector<DrawRequest>() }
}) {
    SDL_GetRendererOutputSize(&renderer, &screen_width_, &screen_height_);
    LOG(INFO) << "Graphics Handler render width: " << screen_width_;
    LOG(INFO) << "Graphics Handler render height: " << screen_height_;
    init(graphic_paths);
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           Rect dest_rect,
                           GraphicPriority priority,
                           bool cleanup,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {

    draw_queue_.at(priority).push_back(
        DrawRequest(texture, dest_rect, cleanup, angle_clockwise, rotation_point));
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           int x_pos,
                           int y_pos,
                           GraphicPriority priority,
                           bool cleanup,
                           double angle_clockwise,
                           SDL_Point* rotation_point) {

    SDL_Rect dest_rect;
    SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h);
    dest_rect.x = x_pos;
    dest_rect.y = y_pos;
    this->draw(texture, dest_rect, priority, cleanup, angle_clockwise, rotation_point);
}

//Cleanup refers to the surface when a SDL_Surface* is passed in
void GraphicsHandler::draw(SDL_Surface* surface,
                           int x_pos,
                           int y_pos,
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
    this->draw(texture, x_pos, y_pos, priority, true, angle_clockwise, rotation_point);
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           Rect dest_rect,
                           GraphicPriority priority,
                           bool cleanup) {

    draw(texture, dest_rect, priority, cleanup, 0, NULL);
}

void GraphicsHandler::draw(SDL_Texture* texture,
                           int x_pos,
                           int y_pos,
                           GraphicPriority priority,
                           bool cleanup) {

    draw(texture, x_pos, y_pos, priority, cleanup, 0, NULL);
}

//Cleanup refers to the surface when a SDL_Surface* is passed in
void GraphicsHandler::draw(SDL_Surface* surface,
                           int x_pos,
                           int y_pos,
                           GraphicPriority priority,
                           bool cleanup) {

    draw(surface, x_pos, y_pos, priority, cleanup, 0, NULL);
}

void GraphicsHandler::update_screen() {
    for (auto priority : DRAW_ORDER) {
        for (auto& draw_request : draw_queue_[priority]) {
            Rect screen_dest_rect = to_screen_coordinate(draw_request.dest_rect());
            draw_request.set_dest_rect(screen_dest_rect);

            SDL_Point screen_rot_pt;

            if (draw_request.rotation_point() != NULL) {
                screen_rot_pt = to_screen_coordinate(*draw_request.rotation_point());
                draw_request.set_rotation_point(&screen_rot_pt);
            }

            SDL_RenderCopyEx(
                &renderer_,
                draw_request.texture(),
                NULL,
                &draw_request.dest_rect(),
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

SDL_Texture* GraphicsHandler::load_image(std::string path) {
    if (game_graphics_.find(path) == game_graphics_.end() ) {
        //TODO allow load_image to call internal_load_image
        LOG(FATAL) << "Fatal error, could not find the sprite " << path.c_str() << "! Exiting...";
    }

    return game_graphics_.find(path)->second;
}

SDL_Texture* GraphicsHandler::internal_load_image(std::string path) {
    SDL_Surface* image_surface = IMG_Load(path.c_str());
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(&renderer_, image_surface);
    SDL_FreeSurface(image_surface);
    return image_texture;
}

SDL_Point GraphicsHandler::to_screen_coordinate(const SDL_Point& point) {
    SDL_Point screen_point;

    double x_ratio = // how far x is between min width and max width
        ((point.x - Util::min_game_width()) / (Util::max_game_width() - Util::min_game_width()));
    screen_point.x = x_ratio * screen_width_;

    double y_ratio = // how far y is between min height and max height
        ((point.y - Util::min_game_height()) / (Util::max_game_height() - Util::min_game_height()));
    screen_point.y = y_ratio * screen_height_;

    return screen_point;
}

Rect GraphicsHandler::to_screen_coordinate(const Rect& rect) {
    Rect screen_rect;

    double x_ratio = // how far x is between min width and max width
        (rect.x - Util::min_game_width()) / (Util::max_game_width() - Util::min_game_width());
    screen_rect.x = x_ratio * screen_width_;

    double y_ratio = // how far y is between min height and max height
        (rect.y - Util::min_game_height()) / (Util::max_game_height() - Util::min_game_height());
    screen_rect.y = y_ratio * screen_height_;

    double width_ratio = // how far width is between min width and max width
        (rect.w) / (Util::max_game_width() - Util::min_game_width());
    screen_rect.w = width_ratio * screen_width_;

    double height_ratio = // how far height is between min height and max height
        (rect.h) / (Util::max_game_height() - Util::min_game_height());
    screen_rect.h = height_ratio * screen_height_;

    LOG(INFO) << "Old game x " << rect.x << " y " << rect.y;
    LOG(INFO) << "New screen x " << screen_rect.x << " y " << screen_rect.y;
    LOG(INFO) << "Old game w " << rect.w << " h " << rect.h;
    LOG(INFO) << "New screen w " << screen_rect.w << " h " << screen_rect.h;
    return screen_rect;
}
