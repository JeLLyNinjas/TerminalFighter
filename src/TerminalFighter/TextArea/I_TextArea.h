#pragma once

class I_TextArea {
public:
    virtual void draw(SDL_Renderer& renderer) = 0;
    virtual void set_color(SDL_Color color) = 0;
};
