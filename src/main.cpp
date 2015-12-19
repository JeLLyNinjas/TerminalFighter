#include <stdio.h>
#include <string>
//hlelo

class Bullet {
public:
    Bullet(std::string my_name) {
        name = my_name;
    }

    void print_name() {
        printf("Bullet: My name is %s\n", name.c_str());
    }

private:
    std::string name;
};

class Nosy_person {

public:
   void pistolFired(Bullet *the_bullet) {
       the_bullet->print_name();
   }
    
};


template <class T>
class Pistol {
    
public: 

    Pistol(Bullet *the_bullet){
        onebullet = the_bullet;
    }

    void print_hello(T* listener){
        listener->pistolFired(onebullet);
    }
private:
    Bullet *onebullet;
};




int main () {

    Nosy_person me; 
    Bullet *the_bullet = new Bullet("Best Bullet");
    Pistol<Nosy_person> my_pistol(the_bullet);
    my_pistol.print_hello(&me);
    


    return 0; 
}
