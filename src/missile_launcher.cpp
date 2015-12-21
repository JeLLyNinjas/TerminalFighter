#include "missile_launcher.h"
#include "missile.h"

Missile * MissileLauncher:: create_missile(std::string name) {
    Missile *return_missile = new Missile(name);
    for (MissileLauncherListener * listener : listeners) { 
        listener->notify_missile_launched(return_missile);
    }

    return  return_missile;
}
