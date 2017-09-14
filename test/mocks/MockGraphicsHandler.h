#pragma once

#include "gmock/gmock.h"

#include "../../src/Engine/GraphicsHandler/I_GraphicsHandler.h"

class MockGraphicsHandler : public I_GraphicsHandler {
public:
    MockGraphicsHandler() {}

    MOCK_METHOD0(init, void());
    MOCK_METHOD6(draw, void(SDL_Texture*, SDL_Rect, GraphicPriority, bool, double, SDL_Point*));
    MOCK_METHOD7(draw, void(SDL_Texture*, int, int, GraphicPriority, bool, double, SDL_Point*));
    MOCK_METHOD7(draw, void(SDL_Surface*, int, int, GraphicPriority, bool, double, SDL_Point*));
    MOCK_METHOD4(draw, void(SDL_Texture*, SDL_Rect, GraphicPriority, bool));
    MOCK_METHOD5(draw, void(SDL_Texture*, int, int, GraphicPriority, bool));
    MOCK_METHOD5(draw, void(SDL_Surface*, int, int, GraphicPriority, bool));

    MOCK_METHOD1(load_image, SDL_Texture * (std::string));
    MOCK_METHOD0(update_screen, void());
};
