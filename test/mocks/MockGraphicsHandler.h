#pragma once

#include "gmock/gmock.h"

#include "../../src/Engine/GraphicsHandler/I_GraphicsHandler.h"

class MockGraphicsHandler : public I_GraphicsHandler {
public:
    MockGraphicsHandler() {}
    ~MockGraphicsHandler() {}

    MOCK_METHOD1(init, void(const std::vector<std::string>&));
    MOCK_METHOD4(create_jn_rect, JN_Rect(double, double, double, double));
    MOCK_METHOD4(create_sdl_rect, SDL_Rect(int, int, int, int));
    MOCK_METHOD7(draw, void(SDL_Texture*, SDL_Rect, JN_Rect, GraphicPriority, bool, double, SDL_Point*));
    MOCK_METHOD7(draw, void(SDL_Surface*, SDL_Rect, JN_Rect, GraphicPriority, bool, double, SDL_Point*));
    MOCK_METHOD6(draw_text, void(std::string, RenderType, std::string, SDL_Color, int, double));

    MOCK_METHOD1(load_image, SDL_Texture * (std::string));
    MOCK_METHOD0(update_screen, void());
};
