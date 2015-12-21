#include <stdio.h>
#include <string>
#include "missile_launcher.h"
#include "observable.h"
#include "missile.h"
#include "missile_launcher_listener.h"


//Interface


class NosyPerson : public MissileLauncherListener {

public:
    NosyPerson(std::string person_name) {
        name = person_name;
    }

    std::string print_name() {
        return name;
    }

    void notify_missile_launched(Missile *missile) {
        printf("Got a notification!!!\n");
        printf("Name of missile is! %s \n", missile->print_name().c_str());
    }

private:
    std::string name;
        
};


int main () {
    MissileLauncher *my_missile_launcher = new MissileLauncher();
    NosyPerson * enoch =  new NosyPerson("enoch has a big nose");
    my_missile_launcher->add_listener(enoch);  
    Missile *big_missile = my_missile_launcher->create_missile("BIG MISSILE!");

    return 0;
}

