#include "game_object.h"

unsigned int GameObject::id_counter_ = 0;

GameObject::GameObject(double x_pos, double y_pos) 
: x_pos_(x_pos)
, y_pos_(y_pos)
, id_(id_counter_++)
{ }

double GameObject::x_pos() { 
	return x_pos_; 
}

double GameObject::y_pos() { 
	return y_pos_; 
}

int GameObject::id() { 
	return id_; 
}

