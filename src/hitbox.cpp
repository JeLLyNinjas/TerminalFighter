#include "hitbox.h"

Hitbox::Hitbox(double x_pos, double y_pos, double width, double height) {
	hitbox_.x = x_pos;
	hitbox_.y = y_pos;
	hitbox_.w = width;
	hitbox_.h = height;
}

Hitbox::Hitbox(SDL_Rect hitbox) {
	hitbox_ = hitbox;
}

bool Hitbox::is_overlapping(const Hitbox& other_hitbox) {
	return SDL_HasIntersection(&hitbox_, &other_hitbox.hitbox());
}

const SDL_Rect& Hitbox::hitbox() const {
	return hitbox_;
}
