import pygame
import math

from gameobject import GameObject

class NotSoBasicGruntProjectile(GameObject):

    def __init__(self, initial_position, target_position, universe):
        self.universe_ = universe

        self.damage_ = 3
        self.id_ = self.create_ID()
        self.listeners_ = []
        self.position_ = initial_position
        self.size_ = 5
        self.speed_ = 15
        self.velocity_ = self.calculate_trajectory(initial_position,
                                                   target_position)

    def calculate_trajectory(self, initial_position, target_position):
        x_distance = target_position[0] - initial_position[0]
        y_distance = target_position[1] - initial_position[1]
        distance = math.sqrt(x_distance**2 + y_distance**2)

        x_velocity = (x_distance * self.speed_) / distance
        y_velocity = (y_distance * self.speed_) / distance

        return x_velocity, y_velocity

    def check_collisions(self):
        collisions = self.universe_.get_collisions(self)
        if collisions:
            collisions[0].take_damage(self.damage_)
            self.report_destroyed()

    def update(self, events):
        self.check_collisions()
        self.position_ = (self.position_[0] + self.velocity_[0],
                          self.position_[1] + self.velocity_[1])

    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_,
                           self.size_)

    """
    Listener Functions
    """

    def report_destroyed(self):
        for listener in self.listeners_:
            listener.reported_destroyed(self)

    def register(self, listeners):
        self.listeners_.append(listeners)


class NotSoBasicGrunt(GameObject):
    

    def __init__(self, starting_position, universe):
        self.position_ = starting_position
        self.universe_ = universe

        self.enemy_type_ = "NotSoBasicGrunt"
        self.health_ = 30
        self.id_ = self.create_ID()
        self.listeners_ = []
        self.size_ = 15
        self.weapon_delay_ = 200
        self.weapon_delay_timer_ = 0
        self.weapon_range_ = 400

        self.x_velocity = 0
        self.y_velocity = 0.3 
        self.x_accel = 0
        self.y_accel = 0

        self.gravity_holes_ = [(500,300)]
        self.gravity_hole_force_ = 0.12

    """
    Update Functions
    """

    def update(self, events):
        forces = [self.calculate_force_from(gravity_hole) 
                  for gravity_hole in self.gravity_holes_]

        self.x_accel = sum([force[0] for force in forces])
        self.y_accel = sum([force[1] for force in forces])

        self.x_velocity += self.x_accel
        self.y_velocity += self.y_accel

        #Space friction, the not_so_basic_grunt will eventuall be at a stanstill
        self.x_velocity *= 0.999999
        self.y_velocity *= 0.997

        self.position_ = (self.position_[0] + self.x_velocity, self.position_[1] + self.y_velocity)

        main_character_position = self.universe_.main_character().position_
        x_distance = main_character_position[0] - self.position_[0]
        y_distance = main_character_position[1] - self.position_[1]
        distance = (x_distance**2 + y_distance**2)**(1/2)

        if distance <= self.weapon_range_ and \
            self.weapon_delay_timer_ >= self.weapon_delay_:  
                new_projectile = NotSoBasicGruntProjectile(self.position_,
                                                           self.universe_.main_character().position_,self.universe_)
                self.universe_.create_enemy_projectile(new_projectile)
                self.weapon_delay_timer_ = 0
        self.weapon_delay_timer_ += 1



    """
    Access Functions
    """

    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_,
                           self.size_)

    def take_damage(self, damage):
        if damage <= 0:
            print("WARNING BasicGrunt " + str(self.id_) + " taking " + str(damage) + " damage")
            print("Disregarding non positive damage")
        elif damage >= self.health_:
            self.report_destroyed()
        else:
            self.health_ -= damage

    def get_type(self):
        return self.enemy_type_
    """"
    Private Functions
    """
    

    def calculate_force_from(self, gravity_hole):
        x_distance = gravity_hole[0] - self.position_[0]
        y_distance = gravity_hole[1] - self.position_[1]

        x_force = self.gravity_hole_force_
        if x_distance < 0:
            x_force *= -1.0

        y_force = self.gravity_hole_force_
        if y_distance < 0:
            y_force *= -1.0

        return x_force, y_force

    """
    Listener Functions
    """

    def report_destroyed(self):
        for listener in self.listeners_:
            listener.reported_destroyed(self)
    
    def register(self, listeners):
        self.listeners_.append(listeners)

