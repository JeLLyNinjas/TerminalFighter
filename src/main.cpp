#include <stdio.h>
#include <string>
#include <map>
#include <iostream>

typedef void (*FnPtr)(void);


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


typedef void (Bullet::*func_ptr_t)();

int main () {

    //Nosy_person me; 
    //Bullet *the_bullet = new Bullet("Best Bullet");
    //Pistol<Nosy_person> my_pistol(the_bullet);
    ////my_pistol.print_hello(&me);

    //// initialization:
    //std::map<std::string, void(Bullet::*)()> myMap;
    //myMap["print_name"] = &Bullet::print_name;

    //// usage:
    //myMap.find("print_name");

    ////std::string s("print_name");
    ////myMap[s](

    //return 0; 
    Bullet abullet("hello");
    std::map<std::string, func_ptr_t> func_map;

    func_map["print_name"] = &Bullet::print_name;

    std::map<std::string, func_ptr_t>::iterator it = func_map.find("print_name");

    if(it != func_map.end())
    {
    func_ptr_t func_ptr = it->second;
    (abullet.*func_ptr)();
    }
    else
    {
    std::cout << "wrong function name!" << std::endl;
    }

    return 0;
}

