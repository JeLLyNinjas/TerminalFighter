#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <vector>


class Missile {
public:
    Missile(std::string missile_name) {
        name = missile_name;
    }
    
    std::string print_name() {
        return name;
    }

private:
    std::string name;
};



//Interface
class MissileLauncherListener {

public: 
    virtual void notify_missile_launched(Missile *missile) = 0;

};

class MissileLauncher {

public:
    Missile * create_missile(std::string name) {
        Missile *return_missile = new Missile(name);
        for (MissileLauncherListener * listener : listeners) { 
            listener->notify_missile_launched(return_missile);
        }

        return  return_missile;
    }

    void add_listener(MissileLauncherListener *listener) {
        listeners.push_back(listener);
    }


private:
    std::vector<MissileLauncherListener *> listeners;
};


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

