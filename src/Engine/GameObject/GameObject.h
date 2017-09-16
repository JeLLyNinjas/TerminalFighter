#pragma once
#include <SDL2/SDL.h>

#include "I_Updatable.h"
#include "CollisionDetector/DestroyedListener.h"
#include "Observable/Observable.h"

class I_GraphicsHandler;
class I_AudioHandler;
class I_Hitbox;


class GameObject : public I_Updatable, public Observable<DestroyedListener> {

public:
    GameObject();
    GameObject(double x_pos, double y_pos, double x_vel, double y_vel, int health);
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void draw(I_GraphicsHandler& graphics) = 0;
    virtual void play(I_AudioHandler& graphics) = 0;
    virtual const I_Hitbox& hitbox() const = 0;
    virtual void notify_collision(GameObject& collided_object) = 0;
    virtual void take_damage(int damage);

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
    int health_;

private:
    static unsigned int id_counter_;
    const unsigned int id_;
};

