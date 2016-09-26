#pragma once
#include <SDL2/SDL.h>

#include "I_Updatable.h"
#include "DestroyedListener.h"
#include "Observable.h"

class GraphicsHandler;
class Hitbox;

class GameObject : public I_Updatable, public Observable<DestroyedListener> {

public:
    GameObject();
    GameObject(double x_pos, double y_pos, double x_vel, double y_vel);
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void draw(GraphicsHandler& graphics) = 0;
    virtual const Hitbox& hitbox() const = 0;
    virtual void notify_collision(GameObject* collided_object) = 0;

    void notify_destroyed();
    double x_pos() const;
    double y_pos() const;
    double x_vel() const;
    double y_vel() const;
    int id() const;

protected:
    double x_pos_;
    double y_pos_;
    double x_vel_;
    double y_vel_;

private:
    static unsigned int id_counter_;
    const unsigned int id_;
};

