#include "hitbox.h"

Hitbox::Hitbox(double x_pos, double y_pos, double width, double height) {
	hitbox_.x = x_pos;
	hitbox_.y = y_pos;
	hitbox_.w = width;
	hitbox_.h = height;

    circle_hitbox_.x = circle_hitbox_.y = circle_hitbox_.r = 0;
}

Hitbox::Hitbox(double x_pos, double y_pos, double radius) {
    circle_hitbox_.x = x_pos;
    circle_hitbox_.y = y_pos;
    circle_hitbox_.r = radius;

    hitbox_.x = hitbox_.y = hitbox_.w = hitbox_.h = 0;
}

Hitbox::Hitbox(SDL_Rect hitbox) {
	hitbox_ = hitbox;
}

Hitbox::Hitbox(Circle hitbox) {
    circle_hitbox_ = hitbox;
}

#if 0
bool Hitbox::is_overlapping(const Hitbox& other_hitbox) {
    return SDL_HasIntersection(&hitbox_, &other_hitbox.hitbox());
}
#endif

#if 0
bool Hitbox::is_overlapping(const Hitbox& other_hitbox) {
    return check_collision(*this, other_hitbox);
}
#endif


bool Hitbox::is_overlapping(Hitbox& other_hitbox) {

    bool is_overlapping;

    // CHECK COLLISION BETWEEN CIRCLES
    if (this->hitbox_.w == 0 && other_hitbox.hitbox_.w == 0)
        is_overlapping = check_collision(this->circle_hitbox_, other_hitbox.circle_hitbox_) ;

    // CHECKS COLLISION BETWEEN RECTS
    else if(this->circle_hitbox_.r == 0 && other_hitbox.circle_hitbox_.r == 0)
        is_overlapping = check_collision(this->hitbox_, other_hitbox.hitbox_);

    // CHECKS COLLISION BETWEEN CIRCLE AND RECT
    else if(this->hitbox_.w == 0 && other_hitbox.circle_hitbox_.r == 0)
        is_overlapping = check_collision(this->circle_hitbox_, other_hitbox.hitbox_);

    // CHECKS COLLISION BETWEEN RECT AND CIRCLE
    else if(this->circle_hitbox_.r == 0 && other_hitbox.hitbox_.w == 0)
        is_overlapping = check_collision(other_hitbox.circle_hitbox_, this->hitbox_);    

    return is_overlapping;
}

bool Hitbox::check_collision(Circle& hitbox, Circle& other_hitbox)
{
    double radiusSquared = hitbox.r + other_hitbox.r;
    radiusSquared = radiusSquared * radiusSquared;

    double delta_x = hitbox.x - other_hitbox.x;
    double delta_y = hitbox.y - other_hitbox.y;
    double distanceSquared = delta_x * delta_x + delta_y * delta_y;

    if (distanceSquared <= radiusSquared)
    {
        return true;
    }

    return false;
}

bool Hitbox::check_collision(Circle &hitbox, SDL_Rect &other_hitbox)
{
   double rect_center_x = (other_hitbox.x + other_hitbox.w)/2;
   double rect_center_y = (other_hitbox.y + other_hitbox.h)/2;

   double distance_x = abs(hitbox.x - rect_center_x);
   double distance_y = abs(hitbox.y - rect_center_y);

   if (distance_x > (other_hitbox.w/2 + hitbox.r))
       return false;
    
   if (distance_y > (other_hitbox.h/2 + hitbox.r))
       return false;
   
   if (distance_x <= (other_hitbox.w/2))
        return true;

   if (distance_y <= (other_hitbox.h/2))
        return true;

   double d_x = (distance_x - other_hitbox.w/2);
   d_x = d_x * d_x;
   double d_y = (distance_y - other_hitbox.h/2);
   d_y = d_y * d_y;

   double cornerDistance_sq = d_x + d_y;
       
   return (cornerDistance_sq <= (hitbox.r * hitbox.r));
}

bool Hitbox::check_collision(SDL_Rect &hitbox, SDL_Rect &other_hitbox)
{
    return SDL_HasIntersection(&hitbox_, &other_hitbox);
}

const SDL_Rect& Hitbox::hitbox() const {
	return hitbox_;
}

const Circle& Hitbox::hitbox_circle() const {
    return circle_hitbox_;
}
