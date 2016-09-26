#pragma once

class I_DrawRequest {
public:
    virtual ~I_DrawRequest() {}
    virtual SDL_Texture* texture() const = 0;
    virtual const SDL_Rect& texture_rect() const = 0;
}
